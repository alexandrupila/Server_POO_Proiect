#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "amessage.h"

class TextMessage : public AMessage
{
protected:
    QString content;
public:
    TextMessage();
    TextMessage(QString content,int sender_id, int chat_id,int message_id=-1);
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
};

#endif // TEXTMESSAGE_H
