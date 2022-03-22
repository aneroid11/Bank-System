#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>

#include "personalaccountwindow.h"

PersonalAccountWindow::PersonalAccountWindow(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle(QString("Роль пользователя: ") + "Клиент");

    QGridLayout* gridLayout = new QGridLayout(this);

    QLabel* userInfoLabel = new QLabel(this);
    userInfoLabel->setText("Информация о пользователе:");

    QTableWidget* infoTable = new QTableWidget(this);
    infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    infoTable->setRowCount(4);
    infoTable->setColumnCount(2);
    infoTable->setItem(0, 0, new QTableWidgetItem("Имя"));
    infoTable->setItem(1, 0, new QTableWidgetItem("Id"));
    infoTable->setItem(2, 0, new QTableWidgetItem("Email"));
    infoTable->setItem(3, 0, new QTableWidgetItem("Телефон"));

    infoTable->setItem(0, 1, new QTableWidgetItem("Лоло опшцуш ывлоа"));
    infoTable->setItem(1, 1, new QTableWidgetItem("234989"));
    infoTable->setItem(2, 1, new QTableWidgetItem("iajdawjidaj@asdjasidi"));
    infoTable->setItem(3, 1, new QTableWidgetItem("+92842394"));

    infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPushButton* openAccount = new QPushButton("Открыть счёт", this);

    QPushButton* closeAccount = new QPushButton("Закрыть счёт", this);

    QPushButton* back = new QPushButton("Назад", this);
    connect(back, &QPushButton::pressed, this, &PersonalAccountWindow::back);

    //int i = 0;
    gridLayout->addWidget(userInfoLabel, 0, 0);
    gridLayout->addWidget(infoTable, 1, 0);
    gridLayout->addWidget(openAccount, 2, 0);
    gridLayout->addWidget(closeAccount, 3, 0);
    gridLayout->addWidget(back, 4, 0);
}

void PersonalAccountWindow::back()
{
    this->close();
    emit showAuthorizationWindow();
}
