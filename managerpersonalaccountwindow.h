#ifndef MANAGERPERSONALACCOUNTWINDOW_H
#define MANAGERPERSONALACCOUNTWINDOW_H

#include <QWidget>
#include <QTableWidget>

#include "manager.h"

class ManagerPersonalAccountWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ManagerPersonalAccountWindow(QWidget *parent = nullptr);
    ~ManagerPersonalAccountWindow();

    void setCurrentManagerData(Manager *mgr);

signals:
    void showAuthorizationWindow();

private slots:
    void back();

private:
    Manager *manager = nullptr;
    QTableWidget* infoTable;
};

#endif // MANAGERPERSONALACCOUNTWINDOW_H
