#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H

#include "amessage.h"
#include "file.h"

class FileMessage : public AMessage
{
protected:
    QString filename;
    QString file_content;
public:
    FileMessage();
    FileMessage(QString filename,QString file_content,int sender_id,int chat_id,QString date, int message_id=-1);
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
    QString getFilename() {return this->filename;}
    QString getFileContent() {return this->file_content;}
};

#endif // FILEMESSAGE_H
