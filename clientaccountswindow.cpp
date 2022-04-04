#include <iostream>

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>

#include "ibanksystemmodel.h"
#include "client.h"
#include "clientaccountswindow.h"

ClientAccountsWindow::ClientAccountsWindow(IBankSystemModel *bankSystem, Client *cl)
    : bankSystemModel(bankSystem), client(cl)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Работа со счетами");

    QGridLayout *gridLayout = new QGridLayout(this);

    QListWidget *accountsListWidget = new QListWidget(this);

    accountsListWidget->insertItem(0, "24918239183293, 2%, на балансе 3000 руб.");
    accountsListWidget->insertItem(1, "90812903912309, 3%, на балансе 440 руб.");
    accountsListWidget->insertItem(2, "31891289819899, 1%, на балансе 4000 руб.");

    QPushButton *openAccount = new QPushButton("Открыть новый счёт", this);
    connect(openAccount, &QPushButton::clicked, this, &ClientAccountsWindow::openAccount);

    QPushButton *closeAccount = new QPushButton("Закрыть счёт", this);
    QPushButton *withdraw = new QPushButton("Снять деньги", this);
    QPushButton *transfer = new QPushButton("Перевести деньги", this);
    QPushButton *putMoney = new QPushButton("Положить деньги", this);

    QPushButton *showAccInfo = new QPushButton("Информация о счёте", this);
    connect(showAccInfo, &QPushButton::clicked, this, &ClientAccountsWindow::showAccountInfo);

    gridLayout->addWidget(accountsListWidget, 0, 0);
    gridLayout->addWidget(showAccInfo, 1, 0);
    gridLayout->addWidget(openAccount, 2, 0);
    gridLayout->addWidget(closeAccount, 3, 0);
    gridLayout->addWidget(withdraw, 4, 0);
    gridLayout->addWidget(transfer, 5, 0);
    gridLayout->addWidget(putMoney, 6, 0);
}

void ClientAccountsWindow::openAccount()
{
    std::cout << "Open account for " << client->getLogin() << "\n";
    bankSystemModel->openAccountForClient(client);
}

void ClientAccountsWindow::showAccountInfo()
{
    QMessageBox msgBox;
    QString info = "Процентная ставка: 2%\n";
    info += "Баланс: 2000 руб.\n";
    info += "Создан: 25.04.22 в 09:00\n";
    msgBox.setWindowTitle("Информация о счёте");
    msgBox.setText(info);
    msgBox.exec();
}
