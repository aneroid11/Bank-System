#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "somethingholdingmoney.h"

class Account : public SomethingHoldingMoney
{
public:
    Account(int64_t id, std::string clientLogin, double initialBalance, double percents, time_t creationTime);

    void accumulate();
};

#endif // ACCOUNT_H
