#include "adminaccountsdepositswindow.h"

#include <QPushButton>
#include <QGridLayout>

AdminAccountsDepositsWindow::AdminAccountsDepositsWindow()
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Счета и вклады");

    QGridLayout *gridLayout = new QGridLayout(this);

    QPushButton *info = new QPushButton("Информация", this);
    QPushButton *ban = new QPushButton("Заблокировать", this);
    QPushButton *freeze = new QPushButton("Заморозить", this);

    gridLayout->addWidget(info, 0, 0);
    gridLayout->addWidget(ban, 1, 0);
    gridLayout->addWidget(freeze, 2, 0);
}
