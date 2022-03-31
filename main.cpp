#include <iostream>

#include <QApplication>

#include "mainwindow.h"
#include "ibanksystemmodel.h"
#include "banksystemmodel.h"

int main(int argc, char *argv[])
{
    IBankSystemModel* bankSystemModel = new BankSystemModel();

    // TODO: убрать
    bankSystemModel->setCurrentBank("Банк \'Стеклянный\'");
    bankSystemModel->addSampleManager();
    bankSystemModel->addSampleOperator();
    bankSystemModel->addSampleAdministrator();
    //bankSystemModel->test();
    //

    QApplication a(argc, argv);
    MainWindow w(bankSystemModel);
    w.show();
    return a.exec();
}
