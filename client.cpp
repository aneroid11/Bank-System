#include <cstdlib>
#include <iostream>

#include "client.h"

Client::Client(const User::Data &clientData, std::string passportData, bool fromRB)
    : User(clientData)
{
    this->passportData = passportData;
    this->fromRB = fromRB;
}
