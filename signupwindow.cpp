#include "signupwindow.h"
#include "ibanksystemmodel.h"

#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>

SignupWindow::SignupWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QWidget(parent), bankSystemModel(bankSystem)
{
    setWindowTitle("Регистрация");
    setFixedSize(400, 400);

    QComboBox *box = new QComboBox(this);
    box->addItem("Клиент");
    box->addItem("Специалист стороннего предприятия");
    box->addItem("Оператор");
    box->addItem("Менеджер");
    box->addItem("Администратор");

    loginLine = new QLineEdit(this);
    loginLine->setPlaceholderText("Придумайте логин");

    passwordLine = new QLineEdit(this);
    passwordLine->setPlaceholderText("Придумайте пароль");
    passwordLine->setEchoMode(QLineEdit::EchoMode::Password);

    nameLine = new QLineEdit(this);
    nameLine->setPlaceholderText("Введите ФИО");

    phoneLine = new QLineEdit(this);
    //phoneLine->setInputMask("+000000000000");
    phoneLine->setPlaceholderText("Введите телефон");

    emailLine = new QLineEdit(this);
    emailLine->setPlaceholderText("Введите E-mail");

    QPushButton *sendRequest = new QPushButton("Отправить запрос на регистрацию", this);
    connect(sendRequest, &QPushButton::pressed, this, &SignupWindow::sendSignupRequest);

    QPushButton *back = new QPushButton("Назад", this);
    connect(back, &QPushButton::pressed, this, &SignupWindow::back);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(box, 0, 0);
    gridLayout->addWidget(loginLine, 1, 0);
    gridLayout->addWidget(passwordLine, 2, 0);
    gridLayout->addWidget(nameLine, 3, 0);
    gridLayout->addWidget(phoneLine, 4, 0);
    gridLayout->addWidget(emailLine, 5, 0);
    gridLayout->addWidget(sendRequest, 6, 0);
    gridLayout->addWidget(back, 7, 0);
}

void SignupWindow::back()
{
    this->close();
    emit showAuthWindow();
}

void SignupWindow::sendSignupRequest()
{
    if (notAllFieldsAreFilled())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Заполните все обязательные поля");
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Запрос отправлен");
    msgBox.setText("Ваша заявка будет рассмотрена менеджером. Пожалуйста, подождите одобрения заявки");
    msgBox.exec();
    back();
}

bool SignupWindow::notAllFieldsAreFilled()
{
    return  loginLine->text().isEmpty() ||
            passwordLine->text().isEmpty() ||
            emailLine->text().isEmpty() ||
            phoneLine->text().isEmpty() ||
            nameLine->text().isEmpty();
}
