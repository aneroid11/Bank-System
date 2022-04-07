#ifndef NOACCOUNTINDBEXCEPTION_H
#define NOACCOUNTINDBEXCEPTION_H

#include <exception>

class NoAccountInDbException : public std::exception
{
public:
    NoAccountInDbException() {}

    const char* what() const noexcept override { return "There is no account with such id in database"; }
};

#endif // NOACCOUNTINDBEXCEPTION_H
