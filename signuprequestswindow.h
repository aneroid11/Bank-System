#ifndef SIGNUPREQUESTSWINDOW_H
#define SIGNUPREQUESTSWINDOW_H

#include <QWidget>
#include <QList>

class IBankSystemModel;
class Client;

class SignupRequestsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SignupRequestsWindow(IBankSystemModel *bankSystem, QWidget *parent = nullptr);
    ~SignupRequestsWindow();

signals:
    void showManagerWindow();

private slots:
    void back();

private:
    QList<Client *> unapprovedClients;
    IBankSystemModel *bankSystemModel;
};

#endif // SIGNUPREQUESTSWINDOW_H
