#ifndef CLIENTACCOUNTSWINDOW_H
#define CLIENTACCOUNTSWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QMap>
#include <QPushButton>

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
    void transferMoney();

    void changeCurrentAccountId(QListWidgetItem *listItem);

private:
    int64_t getCurrentAccountId();

    void deleteClientAccounts();
    void updateClientAccountsData();
    void updateClientAccountsListWidget();

    IBankSystemModel *bankSystemModel;
    Client *client;
    std::list<Account *> clientAccounts;

    QListWidget *accountsListWidget;
    QMap<QString, QPushButton *> buttons;

    int64_t currentAccountId = -1;
};

#endif // CLIENTACCOUNTSWINDOW_H
