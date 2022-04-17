#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>

#include "clientpersonalaccountwindow.h"
#include "clientaccountswindow.h"
#include "clientdepositswindow.h"
#include "clientcreditswindow.h"
#include "clientinstallmentswindow.h"

#include "ibanksystemmodel.h"
#include "client.h"

ClientPersonalAccountWindow::ClientPersonalAccountWindow(IBankSystemModel *bankSystem, Client *client, QWidget *parent)
    : QDialog(parent), currClient(client), bankSystemModel(bankSystem)
{
    setFixedWidth(600);
    setFixedHeight(500);

    setWindowTitle("Личный кабинет клиента");

    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *userInfoLabel = new QLabel(this);
    userInfoLabel->setText("Информация о пользователе:");

    QTableWidget *infoTable = new QTableWidget(this);
    infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    infoTable->setRowCount(6);
    infoTable->setColumnCount(2);
    infoTable->setItem(0, 0, new QTableWidgetItem("Имя"));
    infoTable->setItem(1, 0, new QTableWidgetItem("Id"));
    infoTable->setItem(2, 0, new QTableWidgetItem("Email"));
    infoTable->setItem(3, 0, new QTableWidgetItem("Телефон"));
    infoTable->setItem(4, 0, new QTableWidgetItem("Серия и номер паспорта"));
    infoTable->setItem(5, 0, new QTableWidgetItem("Иностранный клиент?"));

    infoTable->setItem(0, 1, new QTableWidgetItem(currClient->getName().c_str()));
    infoTable->setItem(1, 1, new QTableWidgetItem(std::to_string(currClient->getId()).c_str()));
    infoTable->setItem(2, 1, new QTableWidgetItem(currClient->getEmail().c_str()));
    infoTable->setItem(3, 1, new QTableWidgetItem(currClient->getPhone().c_str()));
    infoTable->setItem(4, 1, new QTableWidgetItem(currClient->getPassportData().c_str()));
    infoTable->setItem(5, 1, new QTableWidgetItem(currClient->isFromRB() ? "Нет" : "Да"));

    infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPushButton *accountsWork = new QPushButton("Счета", this);
    connect(accountsWork, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientAccountsWindow);

    QPushButton *depositsWork = new QPushButton("Вклады", this);
    connect(depositsWork, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientDepositsWindow);

    QPushButton *credits = new QPushButton("Кредиты", this);
    connect(credits, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientCreditsWindow);

    QPushButton *installments = new QPushButton("Рассрочки", this);
    connect(installments, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientInstallmentsWindow);

    QPushButton *salaryProject = new QPushButton("Зарплатный проект", this);
    connect(salaryProject, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showSalaryProjectWindow);

    gridLayout->addWidget(userInfoLabel, 0, 0);
    gridLayout->addWidget(infoTable, 1, 0);
    gridLayout->addWidget(accountsWork, 2, 0);
    gridLayout->addWidget(depositsWork, 3, 0);
    gridLayout->addWidget(credits, 4, 0);
    gridLayout->addWidget(installments, 5, 0);
    gridLayout->addWidget(salaryProject, 6, 0);
}

void ClientPersonalAccountWindow::showClientAccountsWindow()
{
    ClientAccountsWindow *clientAccountsWindow = new ClientAccountsWindow(bankSystemModel, currClient);
    clientAccountsWindow->setWindowModality(Qt::ApplicationModal);
    clientAccountsWindow->exec();
    delete clientAccountsWindow;
}

void ClientPersonalAccountWindow::showClientDepositsWindow()
{
    ClientDepositsWindow *clientDepositsWindow = new ClientDepositsWindow(bankSystemModel, currClient);
    clientDepositsWindow->setWindowModality(Qt::ApplicationModal);
    clientDepositsWindow->exec();
    delete clientDepositsWindow;
}

void ClientPersonalAccountWindow::showClientCreditsWindow()
{
    ClientCreditsWindow *clientCreditsWindow = new ClientCreditsWindow(bankSystemModel, currClient);
    clientCreditsWindow->setWindowModality(Qt::ApplicationModal);
    clientCreditsWindow->exec();
    delete clientCreditsWindow;
}

void ClientPersonalAccountWindow::showClientInstallmentsWindow()
{
    ClientInstallmentsWindow *clientInstallmentsWindow = new ClientInstallmentsWindow();
    clientInstallmentsWindow->setWindowModality(Qt::ApplicationModal);
    clientInstallmentsWindow->exec();
    delete clientInstallmentsWindow;
}

void ClientPersonalAccountWindow::showSalaryProjectWindow()
{
    QString title = QString("Вы действительно хотите подать заявку на зарплатный проект предприятия ");
    title += "ОАО АБУБУ ЛТД КОМПАНИ";
    title += "?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Заявка на зарплатный проект",
                                                              title, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QMessageBox msg;
        msg.setWindowTitle("Заявка подана");
        msg.setText("Пожалуйста, подождите её одобрения оператором");
        msg.exec();
    }
}
