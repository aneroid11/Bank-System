#ifndef WRONGUSERPASSWORDEXCEPTION_H
#define WRONGUSERPASSWORDEXCEPTION_H

#include <exception>

class WrongUserPasswordException : public std::exception
{
public:
    WrongUserPasswordException() {}

    const char *what() const noexcept { return "Password hashes do not match"; }
};

#endif // WRONGUSERPASSWORDEXCEPTION_H
