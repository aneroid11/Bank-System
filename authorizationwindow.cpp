#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>

#include "client.h"
#include "manager.h"

#include "authorizationwindow.h"
#include "clientpersonalaccountwindow.h"
#include "managerpersonalaccountwindow.h"
#include "operatorpersonalaccountwindow.h"
#include "adminpersonalaccountwindow.h"
#include "signupclientwindow.h"
#include "signupspecialistwindow.h"

#include "wronguserpasswordexception.h"

AuthorizationWindow::AuthorizationWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QDialog(parent), bankSystemModel(bankSystem)
{
    setFixedWidth(450);
    setFixedHeight(250);

    loginLine = new QLineEdit(this);
    loginLine->setPlaceholderText("Логин");

    passwordLine = new QLineEdit(this);
    passwordLine->setPlaceholderText("Пароль");
    passwordLine->setEchoMode(QLineEdit::EchoMode::Password);

    QPushButton *enterButton = new QPushButton("Войти", this);
    QPushButton *signupClientButton = new QPushButton("Зарегистрироваться как клиент", this);
    QPushButton *signupSpecialistButton = new QPushButton("Зарегистрироваться как специалист предприятия", this);

    connect(enterButton, &QPushButton::pressed, this, &AuthorizationWindow::enter);
    connect(signupClientButton, &QPushButton::pressed, this, &AuthorizationWindow::signupClient);
    connect(signupSpecialistButton, &QPushButton::pressed, this, &AuthorizationWindow::signupSpecialist);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(loginLine, 0, 0);
    grid->addWidget(passwordLine, 1, 0);
    grid->addWidget(enterButton, 2, 0);
    grid->addWidget(signupClientButton, 3, 0);
    grid->addWidget(signupSpecialistButton, 4, 0);
}

AuthorizationWindow::~AuthorizationWindow()
{
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

        ClientPersonalAccountWindow *clientPersonalAccWindow =
                new ClientPersonalAccountWindow(bankSystemModel, (Client *)loggedInUser);
        clientPersonalAccWindow->setWindowModality(Qt::ApplicationModal);
        clientPersonalAccWindow->exec();

        delete clientPersonalAccWindow;

        delete loggedInUser;
    }
    else if (userType == "MANAGERS")
    {
        ManagerPersonalAccountWindow *managerPersonalAccWindow = new ManagerPersonalAccountWindow(bankSystemModel);

        managerPersonalAccWindow->setCurrentManagerData((Manager *)loggedInUser);
        managerPersonalAccWindow->setWindowModality(Qt::ApplicationModal);
        managerPersonalAccWindow->exec();

        delete managerPersonalAccWindow;
    }
    else if (userType == "OPERATORS")
    {
        OperatorPersonalAccountWindow *win = new OperatorPersonalAccountWindow();
        win->setWindowModality(Qt::ApplicationModal);
        win->exec();
        delete win;
    }
    else if (userType == "ADMINISTRATORS")
    {
        AdminPersonalAccountWindow *adminPersonalAccWindow = new AdminPersonalAccountWindow(bankSystemModel);
        adminPersonalAccWindow->setWindowModality(Qt::ApplicationModal);
        adminPersonalAccWindow->exec();
        delete adminPersonalAccWindow;
    }
}

void AuthorizationWindow::signupClient()
{
    SignupClientWindow *signupWindow = new SignupClientWindow(bankSystemModel);
    signupWindow->setWindowModality(Qt::ApplicationModal);
    signupWindow->exec();
    delete signupWindow;
}

void AuthorizationWindow::signupSpecialist()
{
    SignupSpecialistWindow *signupWindow = new SignupSpecialistWindow(bankSystemModel);
    signupWindow->setWindowModality(Qt::ApplicationModal);
    signupWindow->exec();
    delete signupWindow;
}

void AuthorizationWindow::setBankName(const QString bank)
{
    bankName = bank;
    setWindowTitle(bank + ": авторизация");
}
