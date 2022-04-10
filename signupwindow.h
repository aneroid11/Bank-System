#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>

class QLineEdit;
class QCheckBox;
class IBankSystemModel;

class SignupWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SignupWindow(IBankSystemModel *bankSystem, QWidget *parent = nullptr);

private slots:
    void sendSignupRequest();

private:
    bool notAllFieldsAreFilled();

    QLineEdit *loginLine;
    QLineEdit *passwordLine;
    QLineEdit *nameLine;
    QLineEdit *phoneLine;
    QLineEdit *emailLine;
    QLineEdit *passportDataLine;

    QCheckBox *fromRBCheckBox;

    IBankSystemModel *bankSystemModel;
};

#endif // SIGNUPWINDOW_H
