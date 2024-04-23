#ifndef AMESSAGE_H
#define AMESSAGE_H

#include "imessage.h"

class AMessage : public IMessage
{
public:
    AMessage();
protected:
    int message_id;
    int sender_id;
    int chat_id;
};

#endif // AMESSAGE_H
