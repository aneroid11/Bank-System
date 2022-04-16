#ifndef SOMETHINGHOLDINGMONEY_H
#define SOMETHINGHOLDINGMONEY_H

#include <string>
#include <cstdlib>
#include <ctime>

#include "currencyconverter.h"

const int ACTIVE = 0;
const int CLOSED = 1;
const int FROZEN = 2;
const int BLOCKED = 3;

class SomethingHoldingMoney
{
public:
    SomethingHoldingMoney(int64_t id, std::string clientLogin, double initialBalance,
                          double percents, time_t creationTime, int status, Currency currencyType);
    virtual ~SomethingHoldingMoney() {}

    int64_t getId() const { return id; }
    double getBalance() const { return balance; }
    double getPercents() const { return percents; }

    Currency getCurrencyType() const { return currencyType; }

    time_t getCreationTime() const { return creationTime; }
    std::string getClientLogin() const { return clientLogin; }

    void setStatus(int st) { status = st; }
    int getStatus() const { return status; }

    virtual std::string getInfo() const;

protected:
    int64_t id;
    std::string clientLogin;
    double balance;
    double percents;
    time_t creationTime;

    Currency currencyType;

    int status = ACTIVE;
};

#endif // SOMETHINGHOLDINGMONEY_H
