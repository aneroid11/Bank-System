#include <QPushButton>
#include <QGridLayout>

#include "signuprequestswindow.h"

SignupRequestsWindow::SignupRequestsWindow(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Запросы клиентов на регистрацию");

    QGridLayout *gridLayout = new QGridLayout(this);

    QPushButton *back = new QPushButton("Назад", this);
    connect(back, &QPushButton::pressed, this, &SignupRequestsWindow::back);

    QList<QPushButton *> loginButtons;

    QPushButton *newButton = new QPushButton("Клиент 1", this);
    loginButtons.append(newButton);

    newButton = new QPushButton("Клиент 2", this);
    loginButtons.append(newButton);

    newButton = new QPushButton("Клиент 3", this);
    loginButtons.append(newButton);

    for (QPushButton *currButton : loginButtons)
    {
        connect(currButton, &QPushButton::pressed, this, &SignupRequestsWindow::back);
    }

    QList<QPushButton *> approveButtons;

    for (QPushButton *currButton : loginButtons) {
        newButton = new QPushButton(QString("Подтвердить: ") + currButton->text());
        approveButtons.append(newButton);
    }

    int rowIndex = 0;
    for (; rowIndex < loginButtons.size(); rowIndex++)
    {
        gridLayout->addWidget(loginButtons[rowIndex], rowIndex, 0);
        gridLayout->addWidget(approveButtons[rowIndex], rowIndex, 1);
    }

    gridLayout->addWidget(back, rowIndex, 0);
}

void SignupRequestsWindow::back()
{
    this->close();
    emit showManagerWindow();
}
