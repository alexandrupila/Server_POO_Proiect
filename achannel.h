#ifndef ACHANNEL_H
#define ACHANNEL_H

#include "ichannel.h"
#include "user.h"
#include "groupchat.h"
class AChannel : public IChannel
{
public:
    AChannel();
    QJsonDocument serialize();
    void deserialize(QJsonObject& receivedObj);
protected:
    int channel_id;
    QString channel_name;
    //QVector<User*> user_list;
    //vector fisiere???
    GroupChat channel_chat;
};

#endif // ACHANNEL_H
