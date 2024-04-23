#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

class ISerializable
{
public:
    ISerializable();
    virtual QJsonDocument serialize()=0;
    virtual void deserialize(QJsonObject& receivedObj)=0;
};

#endif // ISERIALIZABLE_H
