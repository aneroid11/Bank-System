#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class AuthorizationWindow;
class QListWidget;
class IBankSystemModel;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(IBankSystemModel* bankSystem, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAuthWindow();

private:
    AuthorizationWindow* authWindow;
    QListWidget* bankListWidget;

    QString selectedBank = "";

    IBankSystemModel* bankSystemModel = nullptr;
};

#endif // MAINWINDOW_H
