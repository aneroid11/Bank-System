#include "adminaccountsdepositswindow.h"
#include "ibanksystemmodel.h"

#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>

AdminAccountsDepositsWindow::AdminAccountsDepositsWindow(IBankSystemModel *bankSystem)
    : bankSystemModel(bankSystem)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Счета и вклады");

    QLabel *accountsListTitle = new QLabel(this);
    accountsListTitle->setText("Счета:");
    QLabel *depositsListTitle = new QLabel(this);
    depositsListTitle->setText("Вклады:");

    accountsListWidget = new QListWidget(this);
    depositsListWidget = new QListWidget(this);

    updateAccountsData();
    updateDepositsData();
    updateAccountsListWidget();
    updateDepositsListWidget();

    QGridLayout *gridLayout = new QGridLayout(this);

    QPushButton *info = new QPushButton("Информация", this);
    connect(info, &QPushButton::clicked, this, &AdminAccountsDepositsWindow::showInfo);

    QPushButton *ban = new QPushButton("Заблокировать", this);
    connect(ban, &QPushButton::clicked, this, &AdminAccountsDepositsWindow::ban);

    QPushButton *freeze = new QPushButton("Заморозить", this);
    connect(freeze, &QPushButton::clicked, this, &AdminAccountsDepositsWindow::freeze);

    gridLayout->addWidget(accountsListTitle, 0, 0);
    gridLayout->addWidget(accountsListWidget, 1, 0);
    gridLayout->addWidget(depositsListTitle, 2, 0);
    gridLayout->addWidget(depositsListWidget, 3, 0);
    gridLayout->addWidget(info, 4, 0);
    gridLayout->addWidget(ban, 5, 0);
    gridLayout->addWidget(freeze, 6, 0);
}

AdminAccountsDepositsWindow::~AdminAccountsDepositsWindow()
{
    deleteAccountsData();
    deleteDepositsData();
}

void AdminAccountsDepositsWindow::deleteAccountsData()
{
    for (Account *a : accounts)
    {
        delete a;
    }
}

void AdminAccountsDepositsWindow::deleteDepositsData()
{
    for (Deposit *d : deposits)
    {
        delete d;
    }
}

void AdminAccountsDepositsWindow::showInfo()
{
    int64_t id = getCurrentSomethingId();
    if (id < 0) { return; }

    SomethingHoldingMoney *something = bankSystemModel->getSomethingHoldingMoneyById(id);
    std::string info = something->getInfo();
    delete something;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация");
    msgBox.setText(info.c_str());
    msgBox.exec();
}

void AdminAccountsDepositsWindow::freeze()
{
    int64_t id = getCurrentSomethingId();
    if (id < 0) { return; }

    bankSystemModel->freeze(id);

    QMessageBox msgBox;
    std::string message = "Заморозка прошла успешно";
    msgBox.setWindowTitle("Информация");
    msgBox.setText(message.c_str());
    msgBox.exec();
}

void AdminAccountsDepositsWindow::ban()
{
    int64_t id = getCurrentSomethingId();
    if (id < 0) { return; }

    bankSystemModel->ban(id);

    QMessageBox msgBox;
    std::string message = "Блокировка прошла успешно";
    msgBox.setWindowTitle("Информация");
    msgBox.setText(message.c_str());
    msgBox.exec();
}

void AdminAccountsDepositsWindow::changeCurrentSomethingId(QListWidgetItem *listItem)
{
    qDebug() << "changeCurrentSomethingId() called\n";
    qDebug() << "currentSomethingId = " << currentSomethingId << "\n";
    currentSomethingId = listItem->text().toInt();
    qDebug() << "after:\n";
    qDebug() << "currentSomethingId = " << currentSomethingId << "\n";
}

void AdminAccountsDepositsWindow::updateAccountsData()
{
    deleteAccountsData();
    accounts = bankSystemModel->getAllAccounts();
}

void AdminAccountsDepositsWindow::updateAccountsListWidget()
{
    accountsListWidget->clear();

    int i = 0;
    for (Account *a : accounts)
    {
        QListWidgetItem *listItem = new QListWidgetItem(std::to_string(a->getId()).c_str(), accountsListWidget);
        accountsListWidget->insertItem(i, listItem);
    }
    connect(accountsListWidget, &QListWidget::itemClicked, this, &AdminAccountsDepositsWindow::changeCurrentSomethingId);
}

void AdminAccountsDepositsWindow::updateDepositsData()
{
    deleteDepositsData();
    deposits = bankSystemModel->getAllDeposits();
}

void AdminAccountsDepositsWindow::updateDepositsListWidget()
{
    depositsListWidget->clear();

    int i = 0;
    for (Deposit *d : deposits)
    {
        depositsListWidget->insertItem(i, std::to_string(d->getId()).c_str());
    }
    connect(depositsListWidget, &QListWidget::itemClicked, this, &AdminAccountsDepositsWindow::changeCurrentSomethingId);
}

int64_t AdminAccountsDepositsWindow::getCurrentSomethingId() const
{
    if (currentSomethingId < 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Вы должны выбрать один из вкладов или счетов");
        msgBox.exec();
        return -1;
    }
    return currentSomethingId;
}
