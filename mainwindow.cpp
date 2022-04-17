#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QMessageBox>

#include "mainwindow.h"
#include "authorizationwindow.h"

MainWindow::MainWindow(IBankSystemModel* bankSystem, const std::list<Bank *> &banks, QWidget *parent)
    : QWidget(parent), bankSystemModel(bankSystem)
{
    setWindowTitle("Управление финансовой системой");
    setFixedSize(size());

    bankListWidget = new QListWidget(this);

    int i = 0;
    for (Bank *b : banks)
    {
        bankListWidget->insertItem(i++, b->name.c_str());
    }

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(bankListWidget, 0, 0);

    QPushButton* authButton = new QPushButton("Авторизоваться", this);
    connect(authButton, &QPushButton::pressed, this, &MainWindow::showAuthWindow);
    grid->addWidget(authButton, 1, 0);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showAuthWindow()
{   
    QList<QListWidgetItem*> selectedBanksList = bankListWidget->selectedItems();

    if (selectedBanksList.size() != 1)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Вы должны выбрать один из банков");
        msgBox.exec();
        return;
    }

    selectedBank = bankListWidget->selectedItems().first()->text();

    bankSystemModel->setCurrentBank(selectedBank.toStdString());

    AuthorizationWindow *authWindow = new AuthorizationWindow(bankSystemModel);
    authWindow->setBankName(selectedBank);
    authWindow->setWindowModality(Qt::ApplicationModal);
    authWindow->exec();
    delete authWindow;
}
