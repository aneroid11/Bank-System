#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "user.h"

class Client : public User
{
public:
    Client(const Data &data, std::string passportData, bool fromRB);

    void approve() { approved = true; }
    bool isApproved() const { return approved; }

    std::string getPassportData() const { return passportData; }
    bool isFromRB() const { return fromRB; }

    std::string getInfo() const override;

private:
    bool approved = false;
    bool fromRB;
    std::string passportData;
};

#endif // CLIENT_H
