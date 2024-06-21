#ifndef PRIVATECHANNEL_H
#define PRIVATECHANNEL_H

#include "achannel.h"

class PrivateChannel : public AChannel
{
public:
    PrivateChannel(QString channel_name,int chat_id,int channel_id=-1)
    {
        this->channel_name=channel_name;
        this->chat_id=chat_id;
        this->channel_id=channel_id;
    }
    PrivateChannel();
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
};

#endif // PRIVATECHANNEL_H
