#include <iostream>

#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

#include "ibanksystemmodel.h"
#include "signuprequestswindow.h"

SignupRequestsWindow::SignupRequestsWindow(IBankSystemModel *bankSystem, QWidget *parent)
    : QDialog(parent), bankSystemModel(bankSystem)
{
    setFixedWidth(500);
    setFixedHeight(500);

    setWindowTitle("Запросы клиентов на регистрацию");

    QGridLayout *gridLayout = new QGridLayout(this);

    unapprovedClients = QList<Client *>::fromStdList(bankSystemModel->getUnapprovedClients());

    QList<QPushButton *> loginButtons;

    for (Client *cl : unapprovedClients)
    {
        QPushButton *newButton = new QPushButton(cl->getLogin().c_str(), this);
        loginButtons.append(newButton);
    }

    for (int i = 0; i < loginButtons.size(); i++)
    {
        connect(loginButtons[i], &QPushButton::pressed,
                this, [this, i]{ showClientInfo(unapprovedClients[i]); });
    }

    QList<QPushButton *> approveButtons;

    for (int i = 0; i < loginButtons.size(); i++)
    {
        QPushButton *currButton = loginButtons[i];

        QPushButton *newButton = new QPushButton(QString("Подтвердить: ") + currButton->text());
        connect(newButton, &QPushButton::pressed,
                this, [this, currButton]{ approveClient(currButton->text().toStdString()); });

        approveButtons.append(newButton);
    }

    int rowIndex = 0;
    for (; rowIndex < loginButtons.size(); rowIndex++)
    {
        gridLayout->addWidget(loginButtons[rowIndex], rowIndex, 0);
        gridLayout->addWidget(approveButtons[rowIndex], rowIndex, 1);
    }
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

void SignupRequestsWindow::showClientInfo(Client *client)
{
    std::string info = client->getInfo();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о клиенте");
    msgBox.setText(info.c_str());
    msgBox.exec();
}

void SignupRequestsWindow::approveClient(std::string login)
{
    bankSystemModel->approveClient(login);

    QMessageBox msgBox;
    msgBox.setWindowTitle("");
    msgBox.setText("Регистрация клиента успешно подтверждена");
    msgBox.exec();
}
