#ifndef DIRECTMESSAGECHAT_H
#define DIRECTMESSAGECHAT_H

#include "achat.h"

class DirectMessageChat : public AChat
{
public:
    DirectMessageChat();
    DirectMessageChat(int id) {this->chat_id=id;}
    DirectMessageChat(int id, QString name) {this->chat_id=id; this->chat_name=name;}
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
};

#endif // DIRECTMESSAGECHAT_H
