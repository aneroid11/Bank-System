#include <iostream>

#include "signupspecialistwindow.h"
#include "ibanksystemmodel.h"
#include "enterprisealreadyexistsexception.h"

#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QCheckBox>
#include <QInputDialog>
#include <QItemSelection>

SignupSpecialistWindow::SignupSpecialistWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QDialog(parent), bankSystemModel(bankSystem)
{
    setWindowTitle("Регистрация специалиста предприятия");
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

    QComboBox *selectEnterprise = new QComboBox(this);
    selectEnterprise->addItem("ыащывщал");
    selectEnterprise->addItem("ыащыdsfasf");
    selectEnterprise->addItem("ыfasащsfasaывщаsffaл");
    selectEnterprise->addItem("asffsыasаsafaщывщал");

    QPushButton *registerEnterprise = new QPushButton("Зарегистрировать предприятие", this);
    connect(registerEnterprise, &QPushButton::pressed, this, &SignupSpecialistWindow::registerEnterprise);

    QPushButton *sendSignupRequest = new QPushButton("Отправить запрос на регистрацию", this);
    connect(sendSignupRequest, &QPushButton::pressed, this, &SignupSpecialistWindow::sendSignupRequest);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(loginLine, 0, 0);
    gridLayout->addWidget(passwordLine, 1, 0);
    gridLayout->addWidget(nameLine, 2, 0);
    gridLayout->addWidget(phoneLine, 3, 0);
    gridLayout->addWidget(emailLine, 4, 0);
    gridLayout->addWidget(selectEnterprise, 5, 0);
    gridLayout->addWidget(registerEnterprise, 6, 0);
    gridLayout->addWidget(sendSignupRequest, 7, 0);
}

void SignupSpecialistWindow::registerEnterprise()
{
    QInputDialog inpDialog;
    QStringList enterpriseTypes;
    enterpriseTypes.append("ИП");
    enterpriseTypes.append("ООО");
    enterpriseTypes.append("ЗАО");
    enterpriseTypes.append("ОАО");
    QString type = inpDialog.getItem(this, "Тип предприятия", "Выберите тип предприятия", enterpriseTypes, 0, false);

    QString enterpriseName;
    bool ok = false;
    do
    {
        enterpriseName = inpDialog.getText(this, "Юридическое название",
                                           "Введите юр. название предприятия",
                                           QLineEdit::Normal, QString(), &ok);

        // проверить, есть ли предприятия с таким названием уже в базе данных, и если есть, то
        // вывести сообщение об этом.
    }
    while (!ok);

    int64_t pan = -1;
    do
    {
        pan = inpDialog.getInt(this, "УНП",
                               "Введите УНП предприятия", 1, 1, 1000000000, 1, &ok);

        // проверить, есть ли предприятия с таким УНП уже в базе данных, и если есть, то
        // вывести сообщение об этом.
    }
    while (!ok);

    QString address = "";
    do
    {
        address = inpDialog.getText(this, "Юридический адрес",
                                    "Введите юридический адрес предприятия", QLineEdit::Normal, QString(), &ok);
    }
    while (!ok);

    // Получить БИК банка, в котором мы сейчас находимся
    int64_t bankBic = bankSystemModel->getCurrentBank()->bic;

    try
    {
        bankSystemModel->registerEnterprise(type.toStdString(), enterpriseName.toStdString(),
                                            pan, bankBic, address.toStdString());
    }
    catch (const EnterpriseAlreadyExistsException &)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Такое предприятие уже существует. Убедитесь, что вы ввели все данные верно");
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Регистрация");

    QString info;
    info += "Вы зарегистрировали предприятие: \n";
    info += "Тип: " + type + "\n";
    info += "Юридическое название: " + enterpriseName + "\n";
    info += "УНП: " + QString::number(pan) + "\n";
    info += "БИК банка: " + QString::number(bankBic) + "\n";
    info += "Юридический адрес: " +  address + "\n";

    msgBox.setText(info);
    msgBox.exec();
}

void SignupSpecialistWindow::sendSignupRequest()
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
        /*bankSystemModel->sendSignupRequestForClient
                (
                    loginLine->text().toStdString(),
                    passwordLine->text().toStdString(),
                    emailLine->text().toStdString(),
                    nameLine->text().toStdString(),
                    phoneLine->text().toStdString(),
                    passportDataLine->text().toStdString(),
                    fromRBCheckBox->checkState() == Qt::CheckState::Checked
                );*/
    }
    catch (const EnterpriseAlreadyExistsException &)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Пользователь с таким логином или номером паспорта уже существует");
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Запрос отправлен");
    msgBox.setText("Ваша заявка будет рассмотрена менеджером. Пожалуйста, подождите одобрения заявки");
    msgBox.exec();

    close();
}

bool SignupSpecialistWindow::notAllFieldsAreFilled()
{
    return  loginLine->text().isEmpty() ||
            passwordLine->text().isEmpty() ||
            emailLine->text().isEmpty() ||
            phoneLine->text().isEmpty() ||
            nameLine->text().isEmpty();
}
