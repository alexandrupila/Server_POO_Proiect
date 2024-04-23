#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H

#include "amessage.h"

class FileMessage : public AMessage
{
protected:
    QString filename;
    QString filecontent;
public:
    FileMessage();
    FileMessage(QString filename,QString filecontent,int sender_id,int chat_id,int message_id=-1);
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
};

#endif // FILEMESSAGE_H
