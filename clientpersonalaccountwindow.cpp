#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>

#include "clientpersonalaccountwindow.h"

ClientPersonalAccountWindow::ClientPersonalAccountWindow(Client *client, QWidget *parent)
    : QDialog(parent), currClient(client)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Личный кабинет клиента");

    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *userInfoLabel = new QLabel(this);
    userInfoLabel->setText("Информация о пользователе:");

    QTableWidget *infoTable = new QTableWidget(this);
    infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    infoTable->setRowCount(4);
    infoTable->setColumnCount(2);
    infoTable->setItem(0, 0, new QTableWidgetItem("Имя"));
    infoTable->setItem(1, 0, new QTableWidgetItem("Id"));
    infoTable->setItem(2, 0, new QTableWidgetItem("Email"));
    infoTable->setItem(3, 0, new QTableWidgetItem("Телефон"));

    infoTable->setItem(0, 1, new QTableWidgetItem(currClient->getName().c_str()));
    infoTable->setItem(1, 1, new QTableWidgetItem(std::to_string(currClient->getId()).c_str()));
    infoTable->setItem(2, 1, new QTableWidgetItem(currClient->getEmail().c_str()));
    infoTable->setItem(3, 1, new QTableWidgetItem(currClient->getPhone().c_str()));

    infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPushButton *accountsWork = new QPushButton("Счета", this);
    QPushButton *depositsWork = new QPushButton("Вклады", this);
    QPushButton *credits = new QPushButton("Кредиты", this);
    QPushButton *installments = new QPushButton("Рассрочки", this);

    gridLayout->addWidget(userInfoLabel, 0, 0);
    gridLayout->addWidget(infoTable, 1, 0);
    gridLayout->addWidget(accountsWork, 2, 0);
    gridLayout->addWidget(depositsWork, 3, 0);
    gridLayout->addWidget(credits, 4, 0);
    gridLayout->addWidget(installments, 5, 0);
}
