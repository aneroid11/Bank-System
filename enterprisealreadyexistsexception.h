#ifndef ENTERPRISEALREADYEXISTSEXCEPTION_H
#define ENTERPRISEALREADYEXISTSEXCEPTION_H

#include <exception>

class EnterpriseAlreadyExistsException : public std::exception
{
public:
    EnterpriseAlreadyExistsException() {}

    const char *what() const noexcept { return "This enterprise already exists in the database"; }
};

#endif // ENTERPRISEALREADYEXISTSEXCEPTION_H
