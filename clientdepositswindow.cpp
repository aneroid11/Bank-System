#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>

#include "clientdepositswindow.h"

ClientDepositsWindow::ClientDepositsWindow()
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Работа со вкладами");

    /*
     * a. Создание
     * a. Закрытие (не надо)
     * e. Накопление
     * */

    QGridLayout *gridLayout = new QGridLayout(this);

    QListWidget *accountsListWidget = new QListWidget(this);

    accountsListWidget->insertItem(0, "24918239183293, 2%, текущая сумма: 3000 руб.");
    accountsListWidget->insertItem(1, "90812903912309, 3%, текущая сумма: 440 руб.");
    accountsListWidget->insertItem(2, "31891289819899, 1%, текущая сумма: 4000 руб.");

    QPushButton *openDeposit = new QPushButton("Открыть новый вклад", this);
    QPushButton *putMoney = new QPushButton("Положить деньги", this);

    gridLayout->addWidget(accountsListWidget, 0, 0);
    gridLayout->addWidget(openDeposit, 1, 0);
    gridLayout->addWidget(putMoney, 2, 0);
}
