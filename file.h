#ifndef FILE_H
#define FILE_H

#include "afile.h"

class File : public AFile
{
public:
    File(QString filename="default_name",QString filecontent="empty");
    QJsonDocument serialize() override;
    virtual void deserialize(QJsonObject& receivedObj) override;
};

#endif // FILE_H
