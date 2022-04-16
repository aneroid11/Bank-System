#ifndef ADMINACCOUNTSDEPOSITSWINDOW_H
#define ADMINACCOUNTSDEPOSITSWINDOW_H

#include <QDialog>
#include <QListWidget>

#include <list>

#include "deposit.h"
#include "account.h"

class IBankSystemModel;

class AdminAccountsDepositsWindow : public QDialog
{
    Q_OBJECT
public:
    AdminAccountsDepositsWindow(IBankSystemModel *bankSystem);
    ~AdminAccountsDepositsWindow();

    void deleteDepositsData();
    void deleteAccountsData();

private slots:
    void showInfo();
    void ban();
    void freeze();
    void changeCurrentSomethingId(QListWidgetItem *listItem);

private:
    void updateAccountsData();
    void updateAccountsListWidget();
    void updateDepositsData();
    void updateDepositsListWidget();

    int64_t getCurrentSomethingId() const;

    IBankSystemModel *bankSystemModel;

    QListWidget *accountsListWidget;
    QListWidget *depositsListWidget;

    std::list<Deposit *> deposits;
    std::list<Account *> accounts;

    int64_t currentSomethingId = -1;
};

#endif // ADMINACCOUNTSDEPOSITSWINDOW_H
