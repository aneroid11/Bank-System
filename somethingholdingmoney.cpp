#include "somethingholdingmoney.h"

SomethingHoldingMoney::SomethingHoldingMoney(int64_t id, std::string clientLogin, double initialBalance,
                                             double percents, time_t creationTime, int status, Currency currencyType)
{
    this->id = id;
    this->clientLogin = clientLogin;
    this->balance = initialBalance;
    this->percents = percents;
    this->creationTime = creationTime;
    this->status = status;
    this->currencyType = currencyType;
}

std::string SomethingHoldingMoney::getInfo() const
{
    std::string info;
    info += "ID: " + std::to_string(id) + "\n";
    info += "Принадлежит: " + clientLogin + "\n";
    info += "Баланс: " + std::to_string(balance);
    info += (currencyType == BYN ? " BYN" : " $");
    info += "\n";
    info += "Процентная ставка: " + std::to_string(percents) + "\n";
    info += "Создан: " + std::string(ctime(&creationTime));

    info += "Статус: ";

    switch (status) {
    case ACTIVE:
        info += "открыт\n";
        break;
    case CLOSED:
        info += "закрыт\n";
        break;
    case FROZEN:
        info += "заморожен\n";
        break;
    default:
        info  += "заблокирован\n";
    }
    return info;
}
