#ifndef ICHAT_H
#define ICHAT_H

#include "iserializable.h"
#include "user.h"
#include "imessage.h"
class IChat : public ISerializable
{
public:
    IChat();
    virtual void addUser(User user_to_add)=0;
    virtual void addMessage(IMessage* new_message)=0;
};

#endif // ICHAT_H
