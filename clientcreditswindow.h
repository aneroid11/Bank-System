#ifndef CLIENTCREDITSWINDOW_H
#define CLIENTCREDITSWINDOW_H

#include <QDialog>
#include <QListWidget>

class ClientCreditsWindow : public QDialog
{
public:
    ClientCreditsWindow();

private:
    QListWidget *creditsListWidget;
};

#endif // CLIENTCREDITSWINDOW_H
