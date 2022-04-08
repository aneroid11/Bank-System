#ifndef ADMINPERSONALACCOUNTWINDOW_H
#define ADMINPERSONALACCOUNTWINDOW_H

#include <QDialog>

class AdminPersonalAccountWindow : public QDialog
{
    Q_OBJECT
public:
    AdminPersonalAccountWindow();

private slots:
    void showAccountsDepositsWindow();
};

#endif // ADMINPERSONALACCOUNTWINDOW_H
