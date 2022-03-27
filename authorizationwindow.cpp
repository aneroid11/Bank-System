#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>

#include "client.h"
#include "manager.h"

#include "authorizationwindow.h"
#include "clientpersonalaccountwindow.h"
#include "managerpersonalaccountwindow.h"
#include "signupwindow.h"

#include "wronguserpasswordexception.h"

AuthorizationWindow::AuthorizationWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QWidget(parent), bankSystemModel(bankSystem)
{
    setFixedWidth(400);
    setFixedHeight(200);

    loginLine = new QLineEdit(this);
    loginLine->setPlaceholderText("Логин");

    passwordLine = new QLineEdit(this);
    passwordLine->setPlaceholderText("Пароль");
    passwordLine->setEchoMode(QLineEdit::EchoMode::Password);

    QPushButton* enterButton = new QPushButton("Войти", this);
    QPushButton* signupButton = new QPushButton("Зарегистрироваться", this);
    QPushButton* backButton = new QPushButton("Назад к выбору банка", this);

    connect(enterButton, &QPushButton::pressed, this, &AuthorizationWindow::enter);
    connect(backButton, &QPushButton::pressed, this, &AuthorizationWindow::back);
    connect(signupButton, &QPushButton::pressed, this, &AuthorizationWindow::signup);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(loginLine, 0, 0);
    grid->addWidget(passwordLine, 1, 0);
    grid->addWidget(enterButton, 2, 0);
    grid->addWidget(signupButton, 3, 0);
    grid->addWidget(backButton, 4, 0);

    clientPersonalAccWindow = new ClientPersonalAccountWindow();
    connect(clientPersonalAccWindow, &ClientPersonalAccountWindow::showAuthorizationWindow,
            this, &AuthorizationWindow::show);

    managerPersonalAccWindow = new ManagerPersonalAccountWindow();
    connect(managerPersonalAccWindow, &ManagerPersonalAccountWindow::showAuthorizationWindow,
            this, &AuthorizationWindow::show);

    signupWindow = new SignupWindow(bankSystem);
    connect(signupWindow, &SignupWindow::showAuthWindow, this, &AuthorizationWindow::show);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete clientPersonalAccWindow;
    delete managerPersonalAccWindow;
    delete signupWindow;
}

void AuthorizationWindow::enter()
{
    QString login = loginLine->text();
    QString password = passwordLine->text();

    try
    {
        bankSystemModel->enter(login.toStdString(), password.toStdString());
    }
    catch (const NoUserInDBException &)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Пользователь не найден");
        msgBox.setText("Пользователя нет в системе. Вы можете зарегистрироваться в ней.");
        msgBox.exec();
        return;
    }
    catch (const WrongUserPasswordException &)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Неверный пароль");
        msgBox.setText("Вы ввели неправильный пароль. Попробуйте ещё раз.");
        msgBox.exec();
        return;
    }

    // Если enter() произошёл успешно, то:
    std::string userType;
    User *loggedInUser = bankSystemModel->getUserData(login.toStdString(), userType);

    if (userType == "CLIENTS")
    {
        Client *client = (Client *)loggedInUser;

        if (!client->isApproved())
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Невозможно войти в личный кабинет");
            msgBox.setText("Ваша заявка на регистрацию ещё не была подтверждена.");
            msgBox.exec();

            delete loggedInUser;
            return;
        }

        this->close();
        clientPersonalAccWindow->show();
        delete loggedInUser;
    }
    else if (userType == "MANAGERS")
    {
        this->close();
        managerPersonalAccWindow->show();
        delete loggedInUser;
    }
}

void AuthorizationWindow::signup()
{
    this->close();
    signupWindow->show();
}

void AuthorizationWindow::back()
{
    this->close();
    emit showMainWindow();
}

void AuthorizationWindow::setBankName(const QString bank)
{
    bankName = bank;
    setWindowTitle(bank + ": авторизация");
}
