#ifndef CLIENTPERSONALACCOUNTWINDOW_H
#define CLIENTPERSONALACCOUNTWINDOW_H

#include <QDialog>

#include "client.h"

class ClientPersonalAccountWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ClientPersonalAccountWindow(Client *client, QWidget *parent = nullptr);

private slots:
    void showClientAccountsWindow();
    void showClientDepositsWindow();
    void showClientCreditsWindow();
    void showClientInstallmentsWindow();
    void showSalaryProjectWindow();

private:
    Client *currClient;
};

#endif // CLIENTPERSONALACCOUNTWINDOW_H
