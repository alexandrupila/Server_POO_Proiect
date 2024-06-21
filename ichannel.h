#ifndef ICHANNEL_H
#define ICHANNEL_H

#include "iserializable.h"
#include "groupchat.h"

class IChannel : public ISerializable
{
public:
    IChannel();
    virtual void setChannelChat(IChat* chat)=0;
    virtual int getChatId()=0;
};

#endif // ICHANNEL_H
