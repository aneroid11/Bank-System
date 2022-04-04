#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "somethingholdingmoney.h"

class Account : public SomethingHoldingMoney
{
public:
    Account(int64_t id, std::string clientLogin, int64_t initialBalance, double percents, time_t creationTime);
};

#endif // ACCOUNT_H
