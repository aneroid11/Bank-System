#include "enterprise.h"

std::string Enterprise::getInfo() const
{
    std::string info;
    info += "Вы зарегистрировали предприятие: \n";
    info += "Тип: " + type + "\n";
    info += "Юридическое название: " + name + "\n";
    info += "УНП: " + std::to_string(pan) + "\n";
    info += "БИК банка: " + std::to_string(bic) + "\n";
    info += "Юридический адрес: " +  address + "\n";
    return info;
}
