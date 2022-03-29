#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>

#include "clientpersonalaccountwindow.h"
#include "clientaccountswindow.h"
#include "clientdepositswindow.h"
#include "clientcreditswindow.h"
#include "clientinstallmentswindow.h"

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
    connect(accountsWork, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientAccountsWindow);

    QPushButton *depositsWork = new QPushButton("Вклады", this);
    connect(depositsWork, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientDepositsWindow);

    QPushButton *credits = new QPushButton("Кредиты", this);
    connect(credits, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientCreditsWindow);

    QPushButton *installments = new QPushButton("Рассрочки", this);
    connect(installments, &QPushButton::clicked, this, &ClientPersonalAccountWindow::showClientInstallmentsWindow);

    gridLayout->addWidget(userInfoLabel, 0, 0);
    gridLayout->addWidget(infoTable, 1, 0);
    gridLayout->addWidget(accountsWork, 2, 0);
    gridLayout->addWidget(depositsWork, 3, 0);
    gridLayout->addWidget(credits, 4, 0);
    gridLayout->addWidget(installments, 5, 0);
}

void ClientPersonalAccountWindow::showClientAccountsWindow()
{
    ClientAccountsWindow *clientAccountsWindow = new ClientAccountsWindow();
    clientAccountsWindow->setWindowModality(Qt::ApplicationModal);
    clientAccountsWindow->exec();
    delete clientAccountsWindow;
}

void ClientPersonalAccountWindow::showClientDepositsWindow()
{
    ClientDepositsWindow *clientDepositsWindow = new ClientDepositsWindow();
    clientDepositsWindow->setWindowModality(Qt::ApplicationModal);
    clientDepositsWindow->exec();
    delete clientDepositsWindow;
}

void ClientPersonalAccountWindow::showClientCreditsWindow()
{
    ClientCreditsWindow *clientCreditsWindow = new ClientCreditsWindow();
    clientCreditsWindow->setWindowModality(Qt::ApplicationModal);
    clientCreditsWindow->exec();
    delete clientCreditsWindow;
}

void ClientPersonalAccountWindow::showClientInstallmentsWindow()
{
    ClientInstallmentsWindow *clientInstallmentsWindow = new ClientInstallmentsWindow();
    clientInstallmentsWindow->setWindowModality(Qt::ApplicationModal);
    clientInstallmentsWindow->exec();
    delete clientInstallmentsWindow;
}
