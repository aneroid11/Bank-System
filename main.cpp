#include <QApplication>

#include "mainwindow.h"
#include "ibanksystemmodel.h"
#include "banksystemmodel.h"

#include "user.h"
#include "database.h"

void testDB()
{
    Database *db = new Database("data.db");

    User::Data userData;
    userData.name = "pfkaodoef";
    userData.email = "akaos@sdokfdsokfo";
    userData.passwordHash = "kapkdaspkdsadksadkdoko";
    userData.phone = "+3402940390";
    userData.login = "oakdasdjis";

    User *u = new User(userData);
    db->addUser(*u);

    delete u;
    delete db;
}

int main(int argc, char *argv[])
{
    testDB();

    IBankSystemModel* bankSystemModel = new BankSystemModel();

    QApplication a(argc, argv);
    MainWindow w(bankSystemModel);
    w.show();
    return a.exec();
}
