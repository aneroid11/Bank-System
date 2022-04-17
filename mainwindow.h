#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <list>

class AuthorizationWindow;
class QListWidget;
class IBankSystemModel;
class Bank;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(IBankSystemModel* bankSystem, const std::list<Bank *> &banks, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAuthWindow();

private:
    QListWidget* bankListWidget;

    QString selectedBank = "";

    IBankSystemModel* bankSystemModel = nullptr;
};

#endif // MAINWINDOW_H
