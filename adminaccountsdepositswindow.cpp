#include "adminaccountsdepositswindow.h"

#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>

AdminAccountsDepositsWindow::AdminAccountsDepositsWindow(IBankSystemModel *bankSystem)
    : bankSystemModel(bankSystem)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Счета и вклады");

    QGridLayout *gridLayout = new QGridLayout(this);

    QPushButton *info = new QPushButton("Информация", this);
    connect(info, &QPushButton::clicked, this, &AdminAccountsDepositsWindow::showInfo);

    QPushButton *ban = new QPushButton("Заблокировать", this);
    connect(ban, &QPushButton::clicked, this, &AdminAccountsDepositsWindow::ban);

    QPushButton *freeze = new QPushButton("Заморозить", this);
    connect(freeze, &QPushButton::clicked, this, &AdminAccountsDepositsWindow::freeze);

    gridLayout->addWidget(info, 0, 0);
    gridLayout->addWidget(ban, 1, 0);
    gridLayout->addWidget(freeze, 2, 0);
}

void AdminAccountsDepositsWindow::showInfo()
{
    QMessageBox msgBox;
    msgBox.setText("adoaskdoas");
    msgBox.exec();
}

void AdminAccountsDepositsWindow::freeze()
{
    QMessageBox msgBox;
    msgBox.setText("adoaskdoas");
    msgBox.exec();
}

void AdminAccountsDepositsWindow::ban()
{
    QMessageBox msgBox;
    msgBox.setText("adoaskdoas");
    msgBox.exec();
}
