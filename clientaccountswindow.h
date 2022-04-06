#ifndef CLIENTACCOUNTSWINDOW_H
#define CLIENTACCOUNTSWINDOW_H

#include <QDialog>
#include <QListWidget>

#include <list>

class IBankSystemModel;
class Client;
class Account;

class ClientAccountsWindow : public QDialog
{
public:
    ClientAccountsWindow(IBankSystemModel *bankSystem, Client *cl);
    ~ClientAccountsWindow();

private slots:
    void openAccount();
    void closeAccount();
    void showAccountInfo();
    void putMoney();
    void withdrawMoney();

private:
    int64_t getCurrentAccountId();

    void deleteClientAccounts();
    void updateClientAccountsData();
    void updateClientAccountsListWidget();

    IBankSystemModel *bankSystemModel;
    Client *client;
    std::list<Account *> clientAccounts;

    QListWidget *accountsListWidget;
};

#endif // CLIENTACCOUNTSWINDOW_H
