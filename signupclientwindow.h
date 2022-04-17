#pragma once

#include <QDialog>

class QLineEdit;
class QCheckBox;
class IBankSystemModel;

class SignupClientWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SignupClientWindow(IBankSystemModel *bankSystem, QWidget *parent = nullptr);

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
