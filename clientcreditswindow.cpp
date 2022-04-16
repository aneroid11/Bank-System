#include <QDebug>
#include <QPushButton>
#include <QGridLayout>

#include "clientcreditswindow.h"

ClientCreditsWindow::ClientCreditsWindow()
{
    setWindowTitle("Управление кредитами");
    setFixedWidth(300);
    setFixedHeight(300);

    QPushButton *takeLoan = new QPushButton("Взять кредит", this);

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(takeLoan, 0, 0);
}
