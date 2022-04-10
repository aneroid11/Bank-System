#include <iostream>

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QInputDialog>

#include "transfer.h"
#include "ibanksystemmodel.h"
#include "client.h"
#include "clientaccountswindow.h"
#include "noaccountindbexception.h"

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
    updateClientAccountsData();
    updateClientAccountsListWidget();

    QPushButton *openAccount = new QPushButton("Открыть новый счёт", this);
    connect(openAccount, &QPushButton::clicked, this, &ClientAccountsWindow::openAccount);

    QPushButton *closeAccount = new QPushButton("Закрыть счёт", this);
    connect(closeAccount, &QPushButton::clicked, this, &ClientAccountsWindow::closeAccount);

    QPushButton *withdraw = new QPushButton("Снять деньги", this);
    connect(withdraw, &QPushButton::clicked, this, &ClientAccountsWindow::withdrawMoney);

    QPushButton *transfer = new QPushButton("Перевести деньги", this);
    connect(transfer, &QPushButton::clicked, this, &ClientAccountsWindow::transferMoney);

    QPushButton *putMoney = new QPushButton("Положить деньги", this);
    connect(putMoney, &QPushButton::clicked, this, &ClientAccountsWindow::putMoney);

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
    deleteClientAccounts();
}

void ClientAccountsWindow::deleteClientAccounts()
{
    for (Account *a : clientAccounts)
    {
        delete a;
    }
}

void ClientAccountsWindow::updateClientAccountsData()
{
    deleteClientAccounts();
    clientAccounts = bankSystemModel->getClientAccountsByStatus(client, ACTIVE);
}

void ClientAccountsWindow::updateClientAccountsListWidget()
{
    accountsListWidget->clear();

    int i = 0;
    for (Account *a : clientAccounts)
    {
        accountsListWidget->insertItem(i, std::to_string(a->getId()).c_str());
    }
}

void ClientAccountsWindow::openAccount()
{
    bankSystemModel->openAccountForClient(client);

    updateClientAccountsData();
    updateClientAccountsListWidget();
}

void ClientAccountsWindow::closeAccount()
{
    // изменить статус текущего аккаунта на CLOSED.
    int64_t accId = getCurrentAccountId();
    if (accId < 0) { return; }

    Account *currAcc = bankSystemModel->getAccountById(accId);
    currAcc->setStatus(CLOSED);
    bankSystemModel->updateAccountData(currAcc);
    delete currAcc;

    updateClientAccountsData();
    updateClientAccountsListWidget();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Закрытие счёта");
    msgBox.setText("Cчёт успешно закрыт");
    msgBox.exec();
}

int64_t ClientAccountsWindow::getCurrentAccountId()
{
    QList<QListWidgetItem*> selectedAccounts = accountsListWidget->selectedItems();

    if (selectedAccounts.size() != 1)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Вы должны выбрать один из счетов");
        msgBox.exec();
        return -1;
    }

    int64_t accId = selectedAccounts[0]->text().toInt();
    return accId;
}

void ClientAccountsWindow::putMoney()
{
    QInputDialog inpDialog;
    bool ok;
    double inpMoney;

    int64_t accId = getCurrentAccountId();

    if (accId == -1) { return; }

    Account *acc = bankSystemModel->getAccountById(accId);
    QString currency = acc->getCurrencyType() == BYN ? "BYN" : "$";
    delete acc;

    do
    {
        QString prompt = "Введите сумму пополнения в ";
        prompt += currency;
        inpMoney = inpDialog.getDouble(this, "Положить деньги", prompt,
                                       0.0,
                                       0.0, 1000.0,
                                       2,
                                       &ok);
    }
    while (!ok);

    bankSystemModel->clientAccountAccumulate(accId);
    bankSystemModel->putMoneyOnAccount(accId, inpMoney);
}

void ClientAccountsWindow::withdrawMoney()
{
    int64_t accId = getCurrentAccountId();
    Account *acc = bankSystemModel->getAccountById(accId);
    QString currency = acc->getCurrencyType() == BYN ? "BYN" : "$";
    double maxWithdrawAmount = (int)acc->getBalance();
    delete acc;

    QInputDialog inpDialog;
    bool ok;
    double inpMoney;

    do
    {
        QString prompt = "Введите сумму (" + currency + ", 0.0 - " + QString::number(maxWithdrawAmount) + ")";
        inpMoney = inpDialog.getDouble(this, "Снять деньги", prompt,
                                       0.0,
                                       0.0, maxWithdrawAmount,
                                       2,
                                       &ok);
    }
    while (!ok);

    bankSystemModel->withdrawMoneyFromAccount(accId, inpMoney);
}

void ClientAccountsWindow::transferMoney()
{
    QInputDialog inpDialog;
    bool ok;
    int64_t recipientId;

    do
    {
        recipientId = inpDialog.getInt(this, "Перевод", "Введите номер счёта, на который будут переведены деньги",
                                       0, 0, 1000000, 1, &ok);
    }
    while (!ok);

    int64_t senderId = getCurrentAccountId();
    Account *currAcc = bankSystemModel->getAccountById(senderId);
    QString currency = currAcc->getCurrencyType() == BYN ? "BYN" : "$";
    double maxValue = (int)currAcc->getBalance();
    double value = 0.0;

    do
    {
        QString prompt = "Введите сумму (" + currency + ", 0.0 - " + QString::number(maxValue) + ")";
        value = inpDialog.getDouble(this, "Перевод", prompt,
                                    0.0, 0.0, maxValue, 2, &ok);
    }
    while (!ok);

    try
    {
        bankSystemModel->createTransfer(senderId, recipientId, value);
    }
    catch (const NoAccountInDbException &)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Перевод");
        msgBox.setText("Такого счёта нет в базе данных банка");
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Перевод");
    msgBox.setText("Деньги успешно переведены");
    msgBox.exec();
}

void ClientAccountsWindow::showAccountInfo()
{
    int64_t accId = getCurrentAccountId();
    if (accId == -1) { return; }

    bankSystemModel->clientAccountAccumulate(accId);

    updateClientAccountsData();
    auto it = std::find_if(std::begin(clientAccounts),
                           std::end(clientAccounts),
                           [&](const Account *acc){ return acc->getId() == accId; } );

    Account *currAcc = *it;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о счёте");

    std::string info;
    info += "Процентная ставка: " + std::to_string(currAcc->getPercents()) + "\n";
    info += "Баланс: " + std::to_string(currAcc->getBalance());
    info += (currAcc->getCurrencyType() == BYN ? " BYN" : " $");
    info += "\n";
    time_t creationTime = currAcc->getCreationTime();
    info += "Последнее накопление: " + std::string(ctime(&creationTime)) + "\n";

    msgBox.setText(info.c_str());
    msgBox.exec();
}
