#ifndef PUBLICCHANNEL_H
#define PUBLICCHANNEL_H

#include "achannel.h"

class PublicChannel : public AChannel
{
public:
    PublicChannel();
    PublicChannel(QString channel_name,int chat_id,int channel_id=-1)
    {
        this->channel_name=channel_name;
        this->chat_id=chat_id;
        this->channel_id=channel_id;
    }
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;

};

#endif // PUBLICCHANNEL_H
