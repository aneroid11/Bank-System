#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "somethingholdingmoney.h"

class Deposit : public SomethingHoldingMoney
{
public:
    Deposit(int64_t id, std::string clientLogin, double initialBalance,
            double percents, time_t creationTime, unsigned term, int status = ACTIVE);

    unsigned getTerm() const { return term; }

private:
    unsigned term;
};

#endif // DEPOSIT_H
