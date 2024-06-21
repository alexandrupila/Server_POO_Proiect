#ifndef AASSIGNMENT_H
#define AASSIGNMENT_H

#include "iassignment.h"
#include "submission.h"

class AAssignment : public IAssignment
{
public:
    AAssignment();
    virtual void setId(int id) override {this->assignment_id=id;}
    virtual void setTeamId(int id) override {this->team_id=id;}
    virtual void setCreatorId(int id) override {this->creator_id=id;}
    virtual void setAssignmentName(QString name) override {this->assignment_name=name;}
    virtual void setDescription(QString description) override {this->description=description;}
    virtual void addSubmission(ISubmission* subm) override {this->submissions.append(subm);}
    virtual void setDueDate(QDate date) override {this->due_date=date;}
    virtual int getId() override{return this->assignment_id;}
    virtual int getCreatorId() override;
    virtual int getTeamId() override;
    virtual QString getAssignmentName() override;
    virtual QString getDescription() override;
    virtual QDate getDate() override;
protected:
    int team_id;
    int assignment_id;
    int creator_id;
    QString assignment_name;
    QString description;
    QDate due_date;
    QVector<ISubmission*> submissions;
};

#endif // AASSIGNMENT_H
