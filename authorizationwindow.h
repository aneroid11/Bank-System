#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

#include "ibanksystemmodel.h"

class QLineEdit;
class PersonalAccountWindow;
class SignupWindow;

class AuthorizationWindow : public QWidget
{
    Q_OBJECT
public:
    AuthorizationWindow(IBankSystemModel* bankSystem, QWidget *parent = nullptr);
    ~AuthorizationWindow();

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

    PersonalAccountWindow* personalAccWindow;
    SignupWindow* signupWindow;
};

#endif // AUTHORIZATIONWINDOW_H
