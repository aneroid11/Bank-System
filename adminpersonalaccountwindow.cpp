#include "adminpersonalaccountwindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

AdminPersonalAccountWindow::AdminPersonalAccountWindow()
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Личный кабинет администратора");

    QGridLayout *gridLayout = new QGridLayout(this);

    QPushButton *accountsWork = new QPushButton("Счета банка", this);
    QPushButton *depositsWork = new QPushButton("Вклады банка", this);

    gridLayout->addWidget(accountsWork, 0, 0);
    gridLayout->addWidget(depositsWork, 1, 0);
}
