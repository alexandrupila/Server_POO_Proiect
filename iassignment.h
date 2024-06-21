#ifndef IASSIGNMENT_H
#define IASSIGNMENT_H

#include "iserializable.h"
#include "isubmission.h"

class IAssignment : public ISerializable
{
public:
    IAssignment();
    virtual void setId(int id)=0;
    virtual void setTeamId(int id)=0;
    virtual void setCreatorId(int id)=0;
    virtual void setAssignmentName(QString name)=0;
    virtual void setDescription(QString description)=0;
    virtual void addSubmission(ISubmission* subm)=0;
    virtual void setDueDate(QDate date)=0;
    virtual int getId()=0;
    virtual int getCreatorId()=0;
    virtual int getTeamId()=0;
    virtual QString getAssignmentName()=0;
    virtual QString getDescription()=0;
    virtual QDate getDate()=0;
};

#endif // IASSIGNMENT_H
