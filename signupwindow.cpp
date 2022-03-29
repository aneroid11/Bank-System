#include "signupwindow.h"
#include "ibanksystemmodel.h"
#include "useralreadyexistsexception.h"

#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>

SignupWindow::SignupWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QDialog(parent), bankSystemModel(bankSystem)
{
    setWindowTitle("Регистрация нового клиента");
    setFixedSize(400, 400);

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

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(loginLine, 0, 0);
    gridLayout->addWidget(passwordLine, 1, 0);
    gridLayout->addWidget(nameLine, 2, 0);
    gridLayout->addWidget(phoneLine, 3, 0);
    gridLayout->addWidget(emailLine, 4, 0);
    gridLayout->addWidget(sendRequest, 5, 0);
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

    try
    {
        bankSystemModel->sendSignupRequestForClient
                (
                    loginLine->text().toStdString(),
                    passwordLine->text().toStdString(),
                    emailLine->text().toStdString(),
                    nameLine->text().toStdString(),
                    phoneLine->text().toStdString()
                );
    }
    catch (const UserAlreadyExistsException &)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Пользователь с таким логином уже существует. Выберите другой логин");
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Запрос отправлен");
    msgBox.setText("Ваша заявка будет рассмотрена менеджером. Пожалуйста, подождите одобрения заявки");
    msgBox.exec();

    close();
}

bool SignupWindow::notAllFieldsAreFilled()
{
    return  loginLine->text().isEmpty() ||
            passwordLine->text().isEmpty() ||
            emailLine->text().isEmpty() ||
            phoneLine->text().isEmpty() ||
            nameLine->text().isEmpty();
}
