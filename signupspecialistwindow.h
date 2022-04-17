#ifndef SIGNUPSPECIALISTWINDOW_H
#define SIGNUPSPECIALISTWINDOW_H

#include <QDialog>

class QLineEdit;
class QCheckBox;
class IBankSystemModel;

class SignupSpecialistWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SignupSpecialistWindow(IBankSystemModel *bankSystem, QWidget *parent = nullptr);

private slots:
    void registerEnterprise();
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

#endif // SIGNUPSPECIALISTWINDOW_H
