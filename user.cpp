#include "user.h"

User::User(const User::Data &userData)
    : data(userData)
{
}

std::string User::getInfo() const
{
    std::string info;
    info += "Имя: " + getName() + "\n";
    info += "Логин: " + getLogin()  + "\n";
    info += "Идентификационный номер: " + std::to_string(getId()) + "\n";
    info += "Email: " + getEmail() + "\n";
    info += "Телефон: " + getPhone() + "\n";
    return info;
}
