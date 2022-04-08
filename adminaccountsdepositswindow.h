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

private:
    IBankSystemModel *bankSystemModel;

    QListWidget *accountsListWidget;
    QListWidget *depositsListWidget;

    std::list<Deposit *> deposits;
    std::list<Account *> accounts;
};

#endif // ADMINACCOUNTSDEPOSITSWINDOW_H
