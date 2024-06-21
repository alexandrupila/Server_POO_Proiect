#ifndef ICHAT_H
#define ICHAT_H

#include "iserializable.h"
#include "user.h"
#include "imessage.h"
class IChat : public ISerializable
{
public:
    IChat();
    virtual void addUser(IUser* user_to_add)=0;
    virtual void addMessage(IMessage* new_message)=0;
    virtual void setUserList(QVector<IUser*> users)=0;
    virtual void setMessageList(QVector<IMessage*> messages)=0;
};

#endif // ICHAT_H
