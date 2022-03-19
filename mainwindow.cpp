#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>

#include "mainwindow.h"
#include "authorizationwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Управление финансовой системой");
    setFixedSize(size());

    QListWidget* listWidget = new QListWidget(this);

    for (int i = 0; i < 50; i++)
    {
        listWidget->insertItem(i, QString("Банк ") + std::to_string(i).c_str());
    }

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(listWidget, 0, 0);

    QPushButton* authButton = new QPushButton("Авторизоваться");
    connect(authButton, &QPushButton::pressed, this, &MainWindow::showAuthWindow);
    grid->addWidget(authButton, 1, 0);

    authWindow = new AuthorizationWindow;
    connect(authWindow, &AuthorizationWindow::showMainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{

}

void MainWindow::showAuthWindow()
{
    this->close();
    authWindow->show();
}
