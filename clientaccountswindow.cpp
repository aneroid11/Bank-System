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

    accountsListWidget = new QListWidget(this);

    // Здесь нужно получать список счетов Клиента из базы данных
    // Отображать нужно только их id'шники
    updateClientAccountsListWidget();

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

ClientAccountsWindow::~ClientAccountsWindow()
{
    for (Account *a : clientAccounts)
    {
        delete a;
    }
}

void ClientAccountsWindow::updateClientAccountsListWidget()
{
    clientAccounts = bankSystemModel->getClientAccounts(client);

    accountsListWidget->clear();

    int i = 0;
    for (Account *a : clientAccounts)
    {
        accountsListWidget->insertItem(i, std::to_string(a->getId()).c_str());
    }
}

void ClientAccountsWindow::openAccount()
{
    std::cout << "Open account for " << client->getLogin() << "\n";
    bankSystemModel->openAccountForClient(client);

    updateClientAccountsListWidget();
}

void ClientAccountsWindow::showAccountInfo()
{
    QList<QListWidgetItem*> selectedAccounts = accountsListWidget->selectedItems();

    if (selectedAccounts.size() != 1)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Вы должны выбрать один из счетов");
        msgBox.exec();
        return;
    }

    int64_t accId = selectedAccounts[0]->text().toInt();
    bankSystemModel->updateClientAccount(accId);

    auto it = std::find_if(std::begin(clientAccounts),
                           std::end(clientAccounts),
                           [&](const Account *acc){ return acc->getId() == accId; } );

    Account *currAcc = *it;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о счёте");

    std::string info;
    info += "Процентная ставка: " + std::to_string(currAcc->getPercents()) + "\n";
    info += "Баланс: " + std::to_string(currAcc->getBalance()) + "\n";
    time_t creationTime = currAcc->getCreationTime();
    info += "Создан: " + std::string(ctime(&creationTime)) + "\n";

    msgBox.setText(info.c_str());
    msgBox.exec();
}
