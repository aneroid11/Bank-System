#ifndef TRANSFER_H
#define TRANSFER_H

#include <cstdlib>
#include <ctime>

class Transfer
{
public:
    Transfer(int64_t id, int64_t sender, int64_t recipient, time_t time, double val);

    int64_t getId() const { return id; }
    int64_t getSenderId() const { return senderId; }
    int64_t getRecipientId() const { return recipientId; }
    time_t getCreationTime() const { return creationTime; }
    double getValue() const { return value; }

private:
    int64_t id;
    int64_t senderId, recipientId;
    time_t creationTime;
    double value;
};

#endif // TRANSFER_H
