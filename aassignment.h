#ifndef AASSIGNMENT_H
#define AASSIGNMENT_H

#include "iassignment.h"

class AAssignment : public IAssignment
{
public:
    AAssignment();
    QJsonDocument serialize();
    void deserialize(QJsonObject& receivedObj);
protected:
    int assignment_id;
    QString assignment_name;
    int creator_id;
    QDate due_date;
    QString description;
    //submission_list
};

#endif // AASSIGNMENT_H
