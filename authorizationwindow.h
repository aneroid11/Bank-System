#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

class AuthorizationWindow : public QWidget
{
    Q_OBJECT
public:
    AuthorizationWindow(QWidget *parent = nullptr);

    void setBankName(const QString bank);

signals:
    void showMainWindow();

private slots:
    void back();

private:
    QString bankName = "";
};

#endif // AUTHORIZATIONWINDOW_H
