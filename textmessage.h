#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "amessage.h"

class TextMessage : public AMessage
{
protected:
    QString content;
public:
    TextMessage();
    TextMessage(QString content,int sender_id, int chat_id,QString date, int message_id=-1);
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
    QString getContent() {return this->content;}
};

#endif // TEXTMESSAGE_H
