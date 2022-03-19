#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

class AuthorizationWindow : public QWidget
{
    Q_OBJECT
public:
    AuthorizationWindow(QWidget *parent = nullptr);

signals:
    void showMainWindow();

private slots:
    void back();
};

#endif // AUTHORIZATIONWINDOW_H
