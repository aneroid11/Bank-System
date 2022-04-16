#ifndef CLIENTCREDITSWINDOW_H
#define CLIENTCREDITSWINDOW_H

#include <QDialog>
#include <QListWidget>

class Client;
class IBankSystemModel;

class ClientCreditsWindow : public QDialog
{
public:
    ClientCreditsWindow(IBankSystemModel *bankSystemModel, Client *client);

private slots:
    void changeCurrentCreditId(QListWidgetItem *item);

    void showCreditInfo();
    void takeLoan();
    void makeMonthlyPayment();

private:
    Client *client;
    IBankSystemModel *bankSystemModel;

    int64_t getCurrentCreditId() const;

    QListWidget *creditsListWidget;
    int64_t currentCreditId = -1;
};

#endif // CLIENTCREDITSWINDOW_H
