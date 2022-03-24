#ifndef CANNOTOPENDBEXCEPTION_H
#define CANNOTOPENDBEXCEPTION_H

#include <exception>
#include <string>

class CannotOpenDBException : public std::exception
{
public:
    CannotOpenDBException(std::string errMsg);

    CannotOpenDBException& operator =(const CannotOpenDBException& exc)
    {
        errorMsg = exc.errorMsg;
        return *this;
    }

    const char *what() const noexcept;

private:
    std::string errorMsg;
};

#endif // CANNOTOPENDBEXCEPTION_H
