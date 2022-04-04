#include <cstdlib>
#include <iostream>

#include "client.h"

Client::Client(const User::Data &clientData)
    : User(clientData)
{
}
