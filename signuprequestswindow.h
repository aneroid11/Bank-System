#ifndef SIGNUPREQUESTSWINDOW_H
#define SIGNUPREQUESTSWINDOW_H

#include <QDialog>
#include <QList>

class IBankSystemModel;
class Client;

class SignupRequestsWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SignupRequestsWindow(IBankSystemModel *bankSystem, QWidget *parent = nullptr);
    ~SignupRequestsWindow();

private:
    void showClientInfo(Client *client);
    void approveClient(std::string login);

    QList<Client *> unapprovedClients;
    IBankSystemModel *bankSystemModel;
};

#endif // SIGNUPREQUESTSWINDOW_H
