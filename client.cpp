#include <cstdlib>
#include <iostream>

#include "client.h"

Client::Client(const User::Data &clientData, std::string passportData, bool fromRB)
    : User(clientData)
{
    this->passportData = passportData;
    this->fromRB = fromRB;
}

std::string Client::getInfo() const
{
    std::string info = User::getInfo();
    info += "Серия и номер паспорта: " + getPassportData() + "\n";
    info += (isFromRB() ? "Гражданин РБ" : "Иностранный клиент");
    return info;
}
