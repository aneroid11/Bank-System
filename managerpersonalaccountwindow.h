#ifndef MANAGERPERSONALACCOUNTWINDOW_H
#define MANAGERPERSONALACCOUNTWINDOW_H

#include <QWidget>

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
};

#endif // MANAGERPERSONALACCOUNTWINDOW_H
