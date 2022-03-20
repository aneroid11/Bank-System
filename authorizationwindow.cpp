#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>

#include "authorizationwindow.h"

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
}

void AuthorizationWindow::enter()
{
    QString login = loginLine->text();
    QString password = passwordLine->text();

    try
    {
        bankSystemModel->enter(login.toStdString(), password.toStdString());
    }
    catch (...) // Придумать класс-исключение для случая, когда нет пользователя в системе.
    {
        QMessageBox msgBox;
        msgBox.setText("Пользователя нет в системе.");
        msgBox.exec();
    }
}

void AuthorizationWindow::signup()
{

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
