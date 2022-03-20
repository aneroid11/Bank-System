#include <QApplication>

#include "mainwindow.h"
#include "ibanksystemmodel.h"
#include "banksystemmodel.h"

int main(int argc, char *argv[])
{
    IBankSystemModel* bankSystemModel = new BankSystemModel();

    QApplication a(argc, argv);
    MainWindow w(bankSystemModel);
    w.show();
    return a.exec();
}
