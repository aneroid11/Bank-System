#ifndef CLIENTPERSONALACCOUNTWINDOW_H
#define CLIENTPERSONALACCOUNTWINDOW_H

#include <QDialog>

class ClientPersonalAccountWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ClientPersonalAccountWindow(QWidget *parent = nullptr);

signals:
    void showAuthorizationWindow();

private slots:
    void back();
};

#endif // CLIENTPERSONALACCOUNTWINDOW_H
