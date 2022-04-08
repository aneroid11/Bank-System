#include "adminpersonalaccountwindow.h"
#include "adminaccountsdepositswindow.h"
#include "ibanksystemmodel.h"

#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

AdminPersonalAccountWindow::AdminPersonalAccountWindow(IBankSystemModel *bankSystem)
    : bankSystemModel(bankSystem)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Личный кабинет администратора");

    QGridLayout *gridLayout = new QGridLayout(this);

    QPushButton *accountsDepositsWork = new QPushButton("Счета и вклады", this);
    connect(accountsDepositsWork, &QPushButton::clicked, this, &AdminPersonalAccountWindow::showAccountsDepositsWindow);

    gridLayout->addWidget(accountsDepositsWork, 0, 0);
}

void AdminPersonalAccountWindow::showAccountsDepositsWindow()
{
    AdminAccountsDepositsWindow window(bankSystemModel);
    window.setWindowModality(Qt::ApplicationModal);
    window.exec();
}
