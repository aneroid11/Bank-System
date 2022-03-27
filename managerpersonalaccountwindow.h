#ifndef MANAGERPERSONALACCOUNTWINDOW_H
#define MANAGERPERSONALACCOUNTWINDOW_H

#include <QWidget>

class ManagerPersonalAccountWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ManagerPersonalAccountWindow(QWidget *parent = nullptr);

signals:
    void showAuthorizationWindow();

private slots:
    void back();
};

#endif // MANAGERPERSONALACCOUNTWINDOW_H
