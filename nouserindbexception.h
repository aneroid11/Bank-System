#ifndef NOUSERINDBEXCEPTION_H
#define NOUSERINDBEXCEPTION_H

#include <exception>

class NoUserInDBException : public std::exception
{
public:
    NoUserInDBException() {}

    const char* what() const noexcept override { return "There is no user with such login or password in database"; }
};

#endif // NOUSERINDBEXCEPTION_H
