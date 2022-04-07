#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QMessageBox>

#include "clientdepositswindow.h"

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

    depositsListWidget->insertItem(0, "249182");
    depositsListWidget->insertItem(1, "908129");
    depositsListWidget->insertItem(2, "318912");

    QPushButton *depositInfo = new QPushButton("Информация о вкладе", this);
    connect(depositInfo, &QPushButton::clicked, this, &ClientDepositsWindow::showDepositInfo);

    QPushButton *openDeposit = new QPushButton("Открыть новый вклад", this);
    QPushButton *putMoney = new QPushButton("Положить деньги", this);

    gridLayout->addWidget(depositsListWidget, 0, 0);
    gridLayout->addWidget(depositInfo, 1, 0);
    gridLayout->addWidget(openDeposit, 2, 0);
    gridLayout->addWidget(putMoney, 3, 0);
}

ClientDepositsWindow::~ClientDepositsWindow()
{
    delete depositsListWidget;
}

void ClientDepositsWindow::showDepositInfo()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о вкладе");
    msgBox.setText("Нет информации");
    msgBox.exec();
}
