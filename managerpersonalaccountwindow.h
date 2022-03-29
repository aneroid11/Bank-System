#ifndef MANAGERPERSONALACCOUNTWINDOW_H
#define MANAGERPERSONALACCOUNTWINDOW_H

#include <QDialog>
#include <QTableWidget>

#include "ibanksystemmodel.h"
#include "manager.h"
#include "signuprequestswindow.h"

class ManagerPersonalAccountWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ManagerPersonalAccountWindow(IBankSystemModel *bankSystem, QWidget *parent = nullptr);
    ~ManagerPersonalAccountWindow();

    void setCurrentManagerData(Manager *mgr);

signals:
    void showAuthorizationWindow();

private slots:
    void back();
    void showSignupRequests();

private:
    Manager *manager = nullptr;
    QTableWidget *infoTable;

    IBankSystemModel *bankSystemModel;
};

#endif // MANAGERPERSONALACCOUNTWINDOW_H
