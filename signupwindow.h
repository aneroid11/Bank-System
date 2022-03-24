#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>

class QLineEdit;

class SignupWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SignupWindow(QWidget *parent = nullptr);

signals:
    void showAuthWindow();

private slots:
    void back();
    void sendSignupRequest();

private:
    bool notAllFieldsAreFilled();

    QLineEdit *loginLine;
    QLineEdit *passwordLine;
    QLineEdit *nameLine;
    QLineEdit *phoneLine;
    QLineEdit *emailLine;
};

#endif // SIGNUPWINDOW_H
