#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QMessageBox>

#include "mainwindow.h"
#include "authorizationwindow.h"

MainWindow::MainWindow(IBankSystemModel* bankSystem, QWidget *parent)
    : QWidget(parent), bankSystemModel(bankSystem)
{
    setWindowTitle("Управление финансовой системой");
    setFixedSize(size());

    bankListWidget = new QListWidget(this);

    bankListWidget->insertItem(0, "Банк \'Стеклянный\'");
    bankListWidget->insertItem(1, "Банк \'Оловянный\'");
    bankListWidget->insertItem(2, "Банк \'Деревянный\'");

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(bankListWidget, 0, 0);

    QPushButton* authButton = new QPushButton("Авторизоваться", this);
    connect(authButton, &QPushButton::pressed, this, &MainWindow::showAuthWindow);
    grid->addWidget(authButton, 1, 0);

    authWindow = new AuthorizationWindow(bankSystemModel);

    connect(authWindow, &AuthorizationWindow::showMainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete authWindow;
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

    this->close();
    authWindow->setBankName(selectedBank);
    authWindow->show();
}
