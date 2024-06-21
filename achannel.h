#ifndef ACHANNEL_H
#define ACHANNEL_H

#include "ichannel.h"
#include "user.h"
#include "groupchat.h"
class AChannel : public IChannel
{
public:
    AChannel();
    virtual void setChannelChat(IChat* chat) override {this->channel_chat=chat;}
    virtual int getChatId() override {return this->chat_id;}
protected:
    int chat_id;
    int channel_id;
    QString channel_name;
    IChat* channel_chat;
};

#endif // ACHANNEL_H
