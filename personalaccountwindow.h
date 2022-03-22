#ifndef PERSONALACCOUNTWINDOW_H
#define PERSONALACCOUNTWINDOW_H

#include <QWidget>

class PersonalAccountWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PersonalAccountWindow(QWidget *parent = nullptr);

signals:
    void showAuthorizationWindow();

private slots:
    void back();
};

#endif // PERSONALACCOUNTWINDOW_H
