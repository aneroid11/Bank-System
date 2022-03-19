#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class AuthorizationWindow;
class QListWidget;

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
    QListWidget* bankListWidget;

    QString selectedBank = "";
};

#endif // MAINWINDOW_H
