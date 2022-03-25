#ifndef BANKSYSTEMMODEL_H
#define BANKSYSTEMMODEL_H

#include "ibanksystemmodel.h"

class Database;

class BankSystemModel : public IBankSystemModel
{
public:
    BankSystemModel();
    ~BankSystemModel();

    void enter(const std::string& login, const std::string& password) override;

private:
    Database* database;
};

#endif // BANKSYSTEMMODEL_H
