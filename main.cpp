#include <iostream>

#include <QApplication>

#include "mainwindow.h"
#include "ibanksystemmodel.h"
#include "banksystemmodel.h"

std::list<Bank *> prepareBanks(IBankSystemModel *bankSystemModel)
{
    std::list<Bank *> banks = bankSystemModel->loadBanksList();

    for (Bank *b : banks)
    {
        bankSystemModel->setCurrentBank(b);
        bankSystemModel->addSampleManager();
        bankSystemModel->addSampleOperator();
        bankSystemModel->addSampleAdministrator();
    }

    return banks;
}

int main(int argc, char *argv[])
{
    IBankSystemModel* bankSystemModel = new BankSystemModel();
    std::list<Bank *> banks = prepareBanks(bankSystemModel);

    QApplication a(argc, argv);
    MainWindow w(bankSystemModel, banks);
    w.show();
    return a.exec();
}
