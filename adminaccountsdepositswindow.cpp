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

/*
ClientDepositsWindow::~ClientDepositsWindow()
{
    deleteClientDepositsData();
}

void ClientDepositsWindow::deleteClientDepositsData()
{
    for (Deposit *d : clientDeposits)
    {
        delete d;
    }
}

int64_t ClientDepositsWindow::getCurrentDepositId()
{
    QList<QListWidgetItem*> selected = depositsListWidget->selectedItems();

    if (selected.size() != 1)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Вы должны выбрать один из вкладов");
        msgBox.exec();
        return -1;
    }

    int64_t depId = selected[0]->text().toInt();
    return depId;
}

void ClientDepositsWindow::updateClientDepositsData()
{
    deleteClientDepositsData();
    //std::list<Deposit *> deposits = bankSystemModel->getClientDeposits(client);

    std::list<Deposit *> deposits = bankSystemModel->getClientDeposits(client);
    clientDeposits = deposits;

    for (Deposit *d : deposits)
    {
        int status = d->getStatus();

        if (status != ACTIVE && status != CLOSED)
        {
            delete d;
            clientDeposits.remove(d);
        }
    }

    for (Deposit *d : clientDeposits)
    {
        std::cout << d->getId() << ": " << d->getStatus() << "\n";
    }
}

void ClientDepositsWindow::updateClientDepositsListWidget()
{
    depositsListWidget->clear();

    int i = 0;
    for (Deposit *d : clientDeposits)
    {
        depositsListWidget->insertItem(i, std::to_string(d->getId()).c_str());
    }
}

void ClientDepositsWindow::showDepositInfo()
{
    int64_t depId = getCurrentDepositId();
    if (depId == -1) { return; }

    bankSystemModel->clientDepositAccumulate(depId);
    bankSystemModel->clientDepositCheckTerm(depId);

    updateClientDepositsData();
    auto it = std::find_if(std::begin(clientDeposits),
                           std::end(clientDeposits),
                           [&](const Deposit *dep){ return dep->getId() == depId; } );

    Deposit *currDep = *it;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о вкладе");

    std::string info;
    info += "Процентная ставка: " + std::to_string(currDep->getPercents()) + " %\n";
    info += "Баланс: " + std::to_string(currDep->getBalance()) + "\n";
    time_t creationTime = currDep->getCreationTime();
    info += "Создан: " + std::string(ctime(&creationTime));
    time_t percentTime = currDep->getLastAccrualOfInterestTime();
    info += "Последнее накопление: " + std::string(ctime(&percentTime));
    info += "Срок вклада: " + std::to_string(currDep->getTerm()) + " месяцев\n";

    if (currDep->getStatus() == ACTIVE)
    {
        info += "Статус: открытый\n";
    }
    else if (currDep->getStatus() == CLOSED)
    {
        info += "Статус: закрытый\n";
    }

    msgBox.setText(info.c_str());
    msgBox.exec();
}
*/

void AdminAccountsDepositsWindow::showInfo()
{
    SomethingHoldingMoney *something = bankSystemModel->getSomethingHoldingMoneyById(currentSomethingId);
    std::string info = something->getInfo();
    delete something;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация");
    msgBox.setText(info.c_str());
    msgBox.exec();
}

void AdminAccountsDepositsWindow::freeze()
{
    QMessageBox msgBox;
    msgBox.setText("adoaskdoas");
    msgBox.exec();
}

void AdminAccountsDepositsWindow::ban()
{
    QMessageBox msgBox;
    msgBox.setText("adoaskdoas");
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
