#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include "directmessagechat.h"

class GroupChat : public DirectMessageChat
{
public:
    GroupChat();
    GroupChat(int chat_id,int creator_id) {this->chat_id=chat_id; this->creator_id=creator_id;}
    QJsonDocument serialize() override;
protected:
    int creator_id;
};

#endif // GROUPCHAT_H
