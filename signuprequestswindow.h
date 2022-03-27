#ifndef SIGNUPREQUESTSWINDOW_H
#define SIGNUPREQUESTSWINDOW_H

#include <QWidget>
#include <QList>

class Client;

class SignupRequestsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SignupRequestsWindow(QWidget *parent = nullptr);

signals:
    void showManagerWindow();

private slots:
    void back();

private:
    QList<Client *> unapprovedClients;
};

#endif // SIGNUPREQUESTSWINDOW_H
