#ifndef USER_H
#define USER_H

#include <string>

class User
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

    User(const Data &data);

    void setPhone(std::string phone) { data.phone = phone; }
    void setEmail(std::string email) { data.email = email; }

    std::string getName() const { return data.name; }
    std::string getPhone() const { return data.phone; }
    std::string getEmail() const { return data.email; }
    int64_t getId() const { return data.id; }
    std::string getLogin() const { return data.login; }
    std::string getPasswordHash() const { return data.passwordHash; }

protected:
    Data data;
};

#endif // USER_H
