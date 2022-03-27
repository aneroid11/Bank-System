#ifndef SIGNUPREQUESTSWINDOW_H
#define SIGNUPREQUESTSWINDOW_H

#include <QWidget>

class SignupRequestsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SignupRequestsWindow(QWidget *parent = nullptr);

signals:
    void showManagerWindow();

private slots:
    void back();
};

#endif // SIGNUPREQUESTSWINDOW_H
