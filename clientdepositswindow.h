#ifndef CLIENTDEPOSITSWINDOW_H
#define CLIENTDEPOSITSWINDOW_H

#include <QDialog>
#include <QListWidget>

class ClientDepositsWindow : public QDialog
{
public:
    ClientDepositsWindow();
    ~ClientDepositsWindow();

private slots:
    void showDepositInfo();

private:
    int64_t getCurrentDepositId();

    QListWidget *depositsListWidget;
};

#endif // CLIENTDEPOSITSWINDOW_H
