#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class AuthorizationWindow;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAuthWindow();

private:
    AuthorizationWindow* authWindow;
};

#endif // MAINWINDOW_H
