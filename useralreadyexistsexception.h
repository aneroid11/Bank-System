#ifndef USERALREADYEXISTSEXCEPTION_H
#define USERALREADYEXISTSEXCEPTION_H

#include <exception>

class UserAlreadyExistsException : public std::exception
{
public:
    UserAlreadyExistsException() {}

    const char *what() const noexcept { return "This user already exists in the database"; }
};

#endif // USERALREADYEXISTSEXCEPTION_H
