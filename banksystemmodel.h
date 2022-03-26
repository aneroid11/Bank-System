#ifndef BANKSYSTEMMODEL_H
#define BANKSYSTEMMODEL_H

#include "ibanksystemmodel.h"

class Database;

class BankSystemModel : public IBankSystemModel
{
public:
    BankSystemModel();
    ~BankSystemModel();

    void setCurrentBank(std::string bankName) override;

    void enter(std::string login, std::string password) override;

    void sendSignupRequestForClient(std::string login, std::string password, std::string email,
                                    std::string name, std::string phone) override;

private:
    Database *database = nullptr;

    std::string currentBank = "";
};

#endif // BANKSYSTEMMODEL_H
