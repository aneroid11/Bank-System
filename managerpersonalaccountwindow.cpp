#include "managerpersonalaccountwindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>

ManagerPersonalAccountWindow::ManagerPersonalAccountWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Личный кабинет менеджера");

    QGridLayout* gridLayout = new QGridLayout(this);

    QLabel* userInfoLabel = new QLabel(this);
    userInfoLabel->setText("Информация:");

    QTableWidget* infoTable = new QTableWidget(this);
    infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    infoTable->setRowCount(4);
    infoTable->setColumnCount(2);
    infoTable->setItem(0, 0, new QTableWidgetItem("Имя"));
    infoTable->setItem(1, 0, new QTableWidgetItem("Id"));
    infoTable->setItem(2, 0, new QTableWidgetItem("Email"));
    infoTable->setItem(3, 0, new QTableWidgetItem("Телефон"));

    // Это происходит в setCurrentManagerData()
    /*
    infoTable->setItem(0, 1, new QTableWidgetItem("Лоло опшцуш ывлоа"));
    infoTable->setItem(1, 1, new QTableWidgetItem("234989"));
    infoTable->setItem(2, 1, new QTableWidgetItem("iajdawjidaj@asdjasidi"));
    infoTable->setItem(3, 1, new QTableWidgetItem("+92842394"));
    */

    infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPushButton* back = new QPushButton("Назад", this);
    connect(back, &QPushButton::pressed, this, &ManagerPersonalAccountWindow::back);

    gridLayout->addWidget(userInfoLabel, 0, 0);
    gridLayout->addWidget(infoTable, 1, 0);
    gridLayout->addWidget(back, 2, 0);
}

ManagerPersonalAccountWindow::~ManagerPersonalAccountWindow()
{
    if (manager)
    {
        delete manager;
        manager = nullptr;
    }
}

void ManagerPersonalAccountWindow::setCurrentManagerData(Manager *mgr)
{
    if (manager)
    {
        delete manager;
    }
    manager = mgr;
}

void ManagerPersonalAccountWindow::back()
{
    this->close();
    emit showAuthorizationWindow();
}
