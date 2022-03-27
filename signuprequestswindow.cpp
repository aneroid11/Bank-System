#include <QPushButton>
#include <QGridLayout>

#include "ibanksystemmodel.h"
#include "signuprequestswindow.h"

SignupRequestsWindow::SignupRequestsWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QWidget(parent), bankSystemModel(bankSystem)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Запросы клиентов на регистрацию");

    QGridLayout *gridLayout = new QGridLayout(this);

    QPushButton *back = new QPushButton("Назад", this);
    connect(back, &QPushButton::pressed, this, &SignupRequestsWindow::back);

    unapprovedClients = QList<Client *>::fromStdList(bankSystemModel->getUnapprovedClients());

    QList<QPushButton *> loginButtons;

    for (Client *cl : unapprovedClients)
    {
        QPushButton *newButton = new QPushButton(cl->getLogin().c_str(), this);
        loginButtons.append(newButton);
    }

    for (QPushButton *currButton : loginButtons)
    {
        connect(currButton, &QPushButton::pressed, this, &SignupRequestsWindow::back);
    }

    QList<QPushButton *> approveButtons;

    for (QPushButton *currButton : loginButtons) {
        QPushButton *newButton = new QPushButton(QString("Подтвердить: ") + currButton->text());
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

SignupRequestsWindow::~SignupRequestsWindow()
{
    if (unapprovedClients.size() > 1)
    {
        for (Client *cl : unapprovedClients)
        {
            delete cl;
        }
    }
}

void SignupRequestsWindow::back()
{
    this->close();
    emit showManagerWindow();
}
