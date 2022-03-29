#include "managerpersonalaccountwindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>

ManagerPersonalAccountWindow::ManagerPersonalAccountWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QDialog(parent), bankSystemModel(bankSystem)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Личный кабинет менеджера");

    QGridLayout* gridLayout = new QGridLayout(this);

    QLabel* userInfoLabel = new QLabel(this);
    userInfoLabel->setText("Информация:");

    infoTable = new QTableWidget(this);
    infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    infoTable->setRowCount(4);
    infoTable->setColumnCount(2);
    infoTable->setItem(0, 0, new QTableWidgetItem("Имя"));
    infoTable->setItem(1, 0, new QTableWidgetItem("Id"));
    infoTable->setItem(2, 0, new QTableWidgetItem("Email"));
    infoTable->setItem(3, 0, new QTableWidgetItem("Телефон"));

    infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPushButton *showClientsSignupRequests = new QPushButton("Запросы на регистрацию", this);
    connect(showClientsSignupRequests, &QPushButton::pressed, this, &ManagerPersonalAccountWindow::showSignupRequests);

    gridLayout->addWidget(userInfoLabel, 0, 0);
    gridLayout->addWidget(infoTable, 1, 0);
    gridLayout->addWidget(showClientsSignupRequests, 2, 0);
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
    // Здесь должна обновляться информация о пользователе в таблице

    if (manager)
    {
        delete manager;
    }
    manager = mgr;

    infoTable->setItem(0, 1, new QTableWidgetItem(mgr->getName().c_str()));
    infoTable->setItem(1, 1, new QTableWidgetItem(std::to_string(mgr->getId()).c_str()));
    infoTable->setItem(2, 1, new QTableWidgetItem(mgr->getEmail().c_str()));
    infoTable->setItem(3, 1, new QTableWidgetItem(mgr->getPhone().c_str()));
}

void ManagerPersonalAccountWindow::showSignupRequests()
{
    SignupRequestsWindow *signupRequestsWindow = new SignupRequestsWindow(bankSystemModel);
    signupRequestsWindow->setWindowModality(Qt::ApplicationModal);
    signupRequestsWindow->exec();
    delete signupRequestsWindow;
}
