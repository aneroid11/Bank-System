#include <QPushButton>
#include <QGridLayout>

#include "authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Авторизация");
    setFixedSize(size());

    QPushButton* example_button = new QPushButton("Кнопка", this);
    QPushButton* back_button = new QPushButton("Назад", this);

    connect(back_button, &QPushButton::pressed, this, &AuthorizationWindow::back);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(example_button, 0, 0);
    grid->addWidget(back_button, 1, 0);
}

void AuthorizationWindow::back()
{
    this->close();
    emit showMainWindow();
}
