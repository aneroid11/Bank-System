#ifndef CLIENTCREDITSWINDOW_H
#define CLIENTCREDITSWINDOW_H

#include <QDialog>
#include <QListWidget>

class ClientCreditsWindow : public QDialog
{
public:
    ClientCreditsWindow();

private slots:
    void changeCurrentCreditId(QListWidgetItem *item);

private:
    int64_t getCurrentCreditId() const;

    QListWidget *creditsListWidget;
    int64_t currentCreditId = -1;
};

#endif // CLIENTCREDITSWINDOW_H
