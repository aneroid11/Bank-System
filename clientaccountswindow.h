#ifndef CLIENTACCOUNTSWINDOW_H
#define CLIENTACCOUNTSWINDOW_H

#include <QDialog>

class IBankSystemModel;
class Client;

class ClientAccountsWindow : public QDialog
{
public:
    ClientAccountsWindow(IBankSystemModel *bankSystem, Client *cl);

private slots:
    void openAccount();
    void showAccountInfo();

private:
    IBankSystemModel *bankSystemModel;
    Client *client;
};

#endif // CLIENTACCOUNTSWINDOW_H
