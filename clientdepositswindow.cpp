#include <iostream>

#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QMessageBox>

#include "clientdepositswindow.h"
#include "ibanksystemmodel.h"

ClientDepositsWindow::ClientDepositsWindow(IBankSystemModel *bankSystem, Client *cl)
    : bankSystemModel(bankSystem), client(cl)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Работа со вкладами");

    /*
     * a. Создание
     * b. Закрытие (не надо)
     * e. Накопление
     * */

    QGridLayout *gridLayout = new QGridLayout(this);

    depositsListWidget = new QListWidget(this);

    // Здесь нужно получать список вкладов Клиента из базы данных
    // Отображать нужно только их id'шники
    updateClientDepositsData();
    updateClientDepositsListWidget();

    depositsListWidget->insertItem(0, "249182");
    depositsListWidget->insertItem(1, "908129");
    depositsListWidget->insertItem(2, "318912");

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
}

void ClientDepositsWindow::updateClientDepositsData()
{
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
    bankSystemModel->openDepositForClient(client);
}
