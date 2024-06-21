#ifndef ASUBMISSION_H
#define ASUBMISSION_H

#include "isubmission.h"

class ASubmission : public ISubmission
{
public:
    ASubmission();
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
    virtual int getAssignId() override {return this->assignment_id;}
    virtual int getUserId() override {return this->user_id;}
    virtual QString getFilename() override {return this->filename;}
    virtual QString getContent() override {return this->file_content;}
    virtual int getGrade() override {return this->grade;}
    virtual void setId(int id) override {this->submission_id=id;}
    virtual void setAssignId(int id) override {this->assignment_id=id;}
    virtual void setUserId(int id) override {this->user_id=id;}
    virtual void setFilename(QString filename) override {this->filename=filename;}
    virtual void setFilecontent(QString content) override {this->file_content=content;}
    virtual void setGrade(int grade=-1) override {this->grade=grade;}
    virtual void setUsername(QString name) override {this->username=name;}
protected:
    int submission_id;
    int user_id;
    QString filename;
    QString file_content;
    QString username;
    int grade;
    int assignment_id;
};

#endif // ASUBMISSION_H
