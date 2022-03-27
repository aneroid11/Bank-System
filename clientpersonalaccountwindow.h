#ifndef CLIENTPERSONALACCOUNTWINDOW_H
#define CLIENTPERSONALACCOUNTWINDOW_H

#include <QWidget>

class ClientPersonalAccountWindow : public QWidget
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
