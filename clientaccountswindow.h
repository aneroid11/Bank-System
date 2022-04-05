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

    void updateClientAccountsListWidget();

private slots:
    void openAccount();
    void showAccountInfo();
    void putMoney();

private:
    IBankSystemModel *bankSystemModel;
    Client *client;
    std::list<Account *> clientAccounts;

    QListWidget *accountsListWidget;
};

#endif // CLIENTACCOUNTSWINDOW_H
