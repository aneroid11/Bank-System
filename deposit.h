#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "somethingholdingmoney.h"

const int DELETED = 4;

class Deposit : public SomethingHoldingMoney
{
public:
    Deposit(int64_t id, std::string clientLogin, double initialBalance,
            double percents, time_t creationTime, unsigned term,
            time_t lastAccrualOfInterestTime, int status = ACTIVE);

    unsigned getTerm() const { return term; }
    time_t getLastAccrualOfInterestTime() const { return lastAccrualOfInterestTime; }

    void accumulate();
    void checkTerm();
    void withdrawMoney(double value);

private:
    time_t lastAccrualOfInterestTime;
    unsigned term;
};

#endif // DEPOSIT_H
