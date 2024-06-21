#ifndef ISUBMISSION_H
#define ISUBMISSION_H

#include "iserializable.h"

class ISubmission : public ISerializable
{
public:
    ISubmission();
    virtual int getAssignId()=0;
    virtual int getUserId()=0;
    virtual int getGrade()=0;
    virtual QString getFilename()=0;
    virtual QString getContent()=0;
    virtual void setId(int id)=0;
    virtual void setAssignId(int id)=0;
    virtual void setUserId(int id)=0;
    virtual void setFilename(QString filename)=0;
    virtual void setFilecontent(QString content)=0;
    virtual void setGrade(int grade=-1)=0;
    virtual void setUsername(QString name)=0;
};

#endif // ISUBMISSION_H
