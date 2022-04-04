#include <iostream>

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>

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

    gridLayout->addWidget(accountsListWidget, 0, 0);
    gridLayout->addWidget(openAccount, 1, 0);
    gridLayout->addWidget(closeAccount, 2, 0);
    gridLayout->addWidget(withdraw, 3, 0);
    gridLayout->addWidget(transfer, 4, 0);
    gridLayout->addWidget(putMoney, 5, 0);
}

void ClientAccountsWindow::openAccount()
{
    std::cout << "Open account for " << client->getLogin() << "\n";
    bankSystemModel->openAccountForClient(client);
}
