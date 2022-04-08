#ifndef CLIENTDEPOSITSWINDOW_H
#define CLIENTDEPOSITSWINDOW_H

#include <QDialog>
#include <QListWidget>

class IBankSystemModel;
class Deposit;
class Client;

class ClientDepositsWindow : public QDialog
{
public:
    ClientDepositsWindow(IBankSystemModel *bankSystem, Client *cl);
    ~ClientDepositsWindow();

private slots:
    void showDepositInfo();
    void openDeposit();
    void withdrawMoney();

private:
    void updateClientDepositsData();
    void updateClientDepositsListWidget();

    void deleteClientDepositsData();

    int64_t getCurrentDepositId();

    IBankSystemModel *bankSystemModel;
    Client *client;

    std::list<Deposit *> clientDeposits;

    QListWidget *depositsListWidget;
};

#endif // CLIENTDEPOSITSWINDOW_H
