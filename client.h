#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "user.h"

class Client : public User
{
public:
    Client(const Data &data);

    void approve() { approved = true; }
    bool isApproved() const { return approved; }

private:
    bool approved = false;
};

#endif // CLIENT_H
