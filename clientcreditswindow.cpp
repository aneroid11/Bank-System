#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

#include "clientcreditswindow.h"

ClientCreditsWindow::ClientCreditsWindow()
{
    setWindowTitle("Управление кредитами");
    setFixedWidth(300);
    setFixedHeight(300);

    QLabel *creditsListLabel = new QLabel("Список кредитов:", this);

    creditsListWidget = new QListWidget(this);
    creditsListWidget->addItem("02942049");

    QPushButton *showInfo = new QPushButton("Информация о кредите", this);
    QPushButton *takeLoan = new QPushButton("Взять кредит", this);
    QPushButton *makeMonthlyPayment = new QPushButton("Совершить платёж по кредиту", this);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(creditsListLabel, 0, 0);
    gridLayout->addWidget(creditsListWidget, 1, 0);
    gridLayout->addWidget(showInfo, 2, 0);
    gridLayout->addWidget(takeLoan, 3, 0);
    gridLayout->addWidget(makeMonthlyPayment, 4, 0);
}
