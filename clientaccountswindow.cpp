#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>

#include "clientaccountswindow.h"

ClientAccountsWindow::ClientAccountsWindow()
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Работа со счетами");

    /*
     *
1) Открывать
2) закрывать
3) хранить
4) снимать деньги
5) Перевод
6) Накопление
7) Блокировка
8) Заморозка
     * */

    QGridLayout *gridLayout = new QGridLayout(this);

    QListWidget *accountsListWidget = new QListWidget(this);

    accountsListWidget->insertItem(0, "24918239183293, 2%, на балансе 3000 руб.");
    accountsListWidget->insertItem(1, "90812903912309, 3%, на балансе 440 руб.");
    accountsListWidget->insertItem(2, "31891289819899, 1%, на балансе 4000 руб.");

    QPushButton *openAccount = new QPushButton("Открыть новый счёт", this);
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
