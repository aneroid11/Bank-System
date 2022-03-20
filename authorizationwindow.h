#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

#include "ibanksystemmodel.h"

class QLineEdit;

class AuthorizationWindow : public QWidget
{
    Q_OBJECT
public:
    AuthorizationWindow(IBankSystemModel* bankSystem, QWidget *parent = nullptr);

    void setBankName(const QString bank);

signals:
    void showMainWindow();

private slots:
    void back();
    void enter();
    void signup();

private:
    QString bankName = "";
    IBankSystemModel* bankSystemModel;
    QLineEdit* loginLine, * passwordLine;
};

#endif // AUTHORIZATIONWINDOW_H
