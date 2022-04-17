#ifndef CLIENTCREDITSWINDOW_H
#define CLIENTCREDITSWINDOW_H

#include <QDialog>
#include <QListWidget>

class Client;
class Credit;
class IBankSystemModel;

class ClientCreditsWindow : public QDialog
{
public:
    ClientCreditsWindow(IBankSystemModel *bankSystemModel, Client *client);
    ~ClientCreditsWindow();

private slots:
    void changeCurrentCreditId(QListWidgetItem *item);

    void showCreditInfo();
    void takeLoan();
    void makeMonthlyPayment();

private:
    void deleteClientCredits();
    void updateClientCreditsData();
    void updateClientCreditsListWidget();

    Client *client;
    IBankSystemModel *bankSystemModel;

    int64_t getCurrentCreditId() const;

    std::list<Credit *> clientCredits;
    QListWidget *creditsListWidget;
    int64_t currentCreditId = -1;
};

#endif // CLIENTCREDITSWINDOW_H
