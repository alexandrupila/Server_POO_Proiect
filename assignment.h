#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "aassignment.h"

class Assignment : public AAssignment
{
public:
    Assignment();
    Assignment(const Assignment& other);
    Assignment(QString name,QString description,int creator_id,QString zi,QString luna,QString an,int id=-1)
    {
        this->assignment_id=id;
        this->assignment_name=name;
        this->description=description;
        this->creator_id=creator_id;

        this->due_date.setDate(an.toInt(),luna.toInt(),zi.toInt());
    }
    QJsonDocument serialize();
    void deserialize(QJsonObject& receivedObj);
};

#endif // ASSIGNMENT_H
