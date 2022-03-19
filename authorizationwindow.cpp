#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

#include "authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(400);
    setFixedHeight(200);

    // сверху два поля «логин» и «пароль», снизу кнопки: «войти», «зарегистрироваться», «назад к выбору банка».

    QLineEdit* loginLine = new QLineEdit(this);
    loginLine->setPlaceholderText("Логин");

    QLineEdit* passwordLine = new QLineEdit(this);
    passwordLine->setPlaceholderText("Пароль");
    passwordLine->setEchoMode(QLineEdit::EchoMode::Password);

    QPushButton* enterButton = new QPushButton("Войти", this);
    QPushButton* signupButton = new QPushButton("Зарегистрироваться", this);
    QPushButton* backButton = new QPushButton("Назад к выбору банка", this);

    connect(backButton, &QPushButton::pressed, this, &AuthorizationWindow::back);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(loginLine, 0, 0);
    grid->addWidget(passwordLine, 1, 0);
    grid->addWidget(enterButton, 2, 0);
    grid->addWidget(signupButton, 3, 0);
    grid->addWidget(backButton, 4, 0);
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
