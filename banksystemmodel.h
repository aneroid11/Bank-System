#ifndef BANKSYSTEMMODEL_H
#define BANKSYSTEMMODEL_H

#include "ibanksystemmodel.h"

class BankSystemModel : public IBankSystemModel
{
public:
    void enter(const std::string& login, const std::string& password) override;

private:
    bool userIsInDatabase(const std::string& login, const std::string& passwordHash) const;
};

#endif // BANKSYSTEMMODEL_H
