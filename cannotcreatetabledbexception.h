#ifndef CANNOTCREATETABLEDBEXCEPTION_H
#define CANNOTCREATETABLEDBEXCEPTION_H

#include <string>
#include <exception>

class CannotCreateTableDBException : public std::exception
{
public:
    CannotCreateTableDBException(std::string errMsg) { errorMessage = errMsg; }

    CannotCreateTableDBException &operator =(const CannotCreateTableDBException &other)
    {
        errorMessage = other.errorMessage;
        return *this;
    }

    const char *what() const noexcept;

private:
    std::string errorMessage;
};

#endif // CANNOTCREATETABLEDBEXCEPTION_H
