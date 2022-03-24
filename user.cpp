#include <cstdlib>

#include "user.h"

User::User(const User::Data &userData)
    : data(userData)
{
    generateId();
}

void User::generateId()
{
    id = rand() % 1000000;

    // Проверка на то, что пользователя с таким же id не существует.
    // (должна быть)
}
