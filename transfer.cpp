#include "transfer.h"

Transfer::Transfer(int64_t id, int64_t sender, int64_t recipient, time_t time, double val)
{
    this->id = id;
    senderId = sender;
    recipientId = recipient;
    creationTime = time;
    value = val;
}
