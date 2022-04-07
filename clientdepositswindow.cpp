#include <iostream>
#include <sstream>

#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QInputDialog>

#include "clientdepositswindow.h"
#include "ibanksystemmodel.h"
#include "deposit.h"
#include "constants.h"

ClientDepositsWindow::ClientDepositsWindow(IBankSystemModel *bankSystem, Client *cl)
    : bankSystemModel(bankSystem), client(cl)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Работа со вкладами");

    /*
     * a. Создание
     * b. Закрытие (как только истёк срок вклада, но НЕ РАНЬШЕ)
     * e. Накопление
     * */

    QGridLayout *gridLayout = new QGridLayout(this);

    depositsListWidget = new QListWidget(this);

    // Здесь нужно получать список вкладов Клиента из базы данных
    // Отображать нужно только их id'шники
    updateClientDepositsData();
    updateClientDepositsListWidget();

    QPushButton *depositInfo = new QPushButton("Информация о вкладе", this);
    connect(depositInfo, &QPushButton::clicked, this, &ClientDepositsWindow::showDepositInfo);

    QPushButton *openDeposit = new QPushButton("Открыть новый вклад", this);
    connect(openDeposit, &QPushButton::clicked, this, &ClientDepositsWindow::openDeposit);

    QPushButton *putMoney = new QPushButton("Положить деньги", this);

    gridLayout->addWidget(depositsListWidget, 0, 0);
    gridLayout->addWidget(depositInfo, 1, 0);
    gridLayout->addWidget(openDeposit, 2, 0);
    gridLayout->addWidget(putMoney, 3, 0);
}

ClientDepositsWindow::~ClientDepositsWindow()
{
    deleteClientDepositsData();
}

void ClientDepositsWindow::deleteClientDepositsData()
{
    for (Deposit *d : clientDeposits)
    {
        delete d;
    }
}

void ClientDepositsWindow::updateClientDepositsData()
{
    deleteClientDepositsData();

    std::cout << "update client deposits data\n";
}

void ClientDepositsWindow::updateClientDepositsListWidget()
{
    std::cout << "update client deposits list widget\n";
}

void ClientDepositsWindow::showDepositInfo()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о вкладе");
    msgBox.setText("Нет информации");
    msgBox.exec();
}

void ClientDepositsWindow::openDeposit()
{
    // Нужно запросить у Клиента:
    // - Срок вклада в месяцах
    // - Сумму вклада
    QInputDialog inpDialog;
    bool ok;

    unsigned term = 0;
    do
    {
        std::stringstream ss;
        ss << "Введите срок вклада (в месяцах, от " << MIN_DEPOSIT_TERM << " до " << MAX_DEPOSIT_TERM << ")";
        term = inpDialog.getInt(this, "Срок вклада", ss.str().c_str(), 3, MIN_DEPOSIT_TERM, MAX_DEPOSIT_TERM, 1, &ok);
    }
    while (!ok);

    double sum = 0;
    do
    {
        sum = inpDialog.getDouble(this, "Сумма вклада", "Сумма вклада (BYN, 1 - 1000)", 1.0, 1.0, 1000.0, 2, &ok);
    }
    while (!ok);

    bankSystemModel->openDepositForClient(client, term, sum);
}
