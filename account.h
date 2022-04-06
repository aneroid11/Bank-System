#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "somethingholdingmoney.h"

const int ACTIVE = 0;
const int CLOSED = 1;
const int FROZEN = 2;
const int BLOCKED = 3;

class Account : public SomethingHoldingMoney
{
public:
    Account(int64_t id, std::string clientLogin, double initialBalance,
            double percents, time_t creationTime, int st = ACTIVE);

    void accumulate();
    void putMoney(double value) { balance += value; }
    void withdrawMoney(double value) { balance -= value; }

    void setStatus(int st) { status = st; }
    int getStatus() const { return status; }

private:
    int status = ACTIVE;
};

#endif // ACCOUNT_H
