#ifndef ADMINACCOUNTSDEPOSITSWINDOW_H
#define ADMINACCOUNTSDEPOSITSWINDOW_H

#include <QDialog>

class IBankSystemModel;

class AdminAccountsDepositsWindow : public QDialog
{
    Q_OBJECT
public:
    AdminAccountsDepositsWindow(IBankSystemModel *bankSystem);

private slots:
    void showInfo();
    void ban();
    void freeze();

private:
    IBankSystemModel *bankSystemModel;
};

#endif // ADMINACCOUNTSDEPOSITSWINDOW_H
