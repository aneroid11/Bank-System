#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
public:
    struct Data
    {
        int64_t id;
        std::string name;
        std::string phone;
        std::string email;
        std::string login;
        std::string passwordHash;
    };

    Client(const Data &data);

    void setPhone(std::string phone) { data.phone = phone; }
    void setEmail(std::string email) { data.email = email; }

    std::string getName() const { return data.name; }
    std::string getPhone() const { return data.phone; }
    std::string getEmail() const { return data.email; }
    int64_t getId() const { return data.id; }
    std::string getLogin() const { return data.login; }
    std::string getPasswordHash() const { return data.passwordHash; }

    void approve() { approved = true; }
    bool isApproved() const { return approved; }

private:
    Data data;
    bool approved = false;
};

#endif // CLIENT_H
