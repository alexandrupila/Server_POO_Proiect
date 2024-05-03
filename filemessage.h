#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H

#include "amessage.h"
#include "file.h"

class FileMessage : public AMessage
{
protected:
    File file;
public:
    FileMessage();
    FileMessage(File file,int sender_id,int chat_id,int message_id=-1);
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
};

#endif // FILEMESSAGE_H
