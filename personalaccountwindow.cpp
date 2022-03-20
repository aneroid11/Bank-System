#include <QPushButton>
#include <QGridLayout>

#include "personalaccountwindow.h"

PersonalAccountWindow::PersonalAccountWindow(QWidget *parent) : QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout(this);

    QPushButton* back = new QPushButton("Назад", this);
    connect(back, &QPushButton::pressed, this, &PersonalAccountWindow::back);

    gridLayout->addWidget(back, 0, 0);
}

void PersonalAccountWindow::back()
{
    this->close();
    emit showAuthorizationWindow();
}
