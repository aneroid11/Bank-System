#ifndef PERSONALACCOUNTWINDOW_H
#define PERSONALACCOUNTWINDOW_H

#include <QWidget>

class PersonalAccountWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PersonalAccountWindow(QWidget *parent = nullptr);

private slots:
    void back();

signals:
    void showAuthorizationWindow();
};

#endif // PERSONALACCOUNTWINDOW_H
