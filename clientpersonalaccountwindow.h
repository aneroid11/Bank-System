#ifndef CLIENTPERSONALACCOUNTWINDOW_H
#define CLIENTPERSONALACCOUNTWINDOW_H

#include <QDialog>

class Client;
class IBankSystemModel;

class ClientPersonalAccountWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ClientPersonalAccountWindow(IBankSystemModel *bankSystemModel, Client *client, QWidget *parent = nullptr);

private slots:
    void showClientAccountsWindow();
    void showClientDepositsWindow();
    void showClientCreditsWindow();
    void showClientInstallmentsWindow();
    void showSalaryProjectWindow();

private:
    Client *currClient;
    IBankSystemModel *bankSystemModel;
};

#endif // CLIENTPERSONALACCOUNTWINDOW_H
