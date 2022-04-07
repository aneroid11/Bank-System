#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "somethingholdingmoney.h"

class Deposit : public SomethingHoldingMoney
{
public:
    Deposit(int64_t id, std::string clientLogin, double initialBalance,
            double percents, time_t creationTime, int status = ACTIVE);
};

#endif // DEPOSIT_H
