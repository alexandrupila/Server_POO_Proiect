#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QObject>
#include "iserializable.h"

class IMessage : public ISerializable
{
public:
    IMessage();
    virtual int getChatId()=0;
    virtual int getSenderId()=0;
    virtual int getMessageId()=0;
    virtual QString getDate()=0;
    virtual QString getSenderName()=0;
    virtual void setSenderId(int id)=0;
    virtual void setChatId(int id)=0;
    virtual void setSenderName(QString name)=0;
};

#endif // IMESSAGE_H
