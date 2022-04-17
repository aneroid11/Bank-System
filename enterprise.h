#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include <string>

#include "iinforming.h"

class Enterprise : IInforming
{
public:
    Enterprise(int64_t id, std::string type, std::string name, int64_t pan, int64_t bic, std::string address)
    {
        this->id = id;
        this->type = type;
        this->name = name;
        this->pan = pan;
        this->bic = bic;
        this->address = address;
    }
    virtual ~Enterprise() {}

    int64_t getId() const { return id; }
    std::string getType() const { return type; }
    std::string getName() const { return name; }
    int64_t getPan() const { return pan; }
    int64_t getBic() const { return bic; }
    std::string getAddress() const { return address; }

    std::string getInfo() const override;

private:
    int64_t id;
    std::string type;
    std::string name;
    int64_t pan;
    int64_t bic;
    std::string address;
};

#endif // ENTERPRISE_H
