#ifndef ATEAM_H
#define ATEAM_H

#include "iteam.h"
#include "achannel.h"
#include "assignment.h"
#include "admin.h"
#include <QVector>
class ATeam : public ITeam
{
public:
    ATeam();
    void setId(int id) {this->team_id=id;}
    void setCreator_id(int id) {this->creator_id=id;}
    void setTeamName(QString name) {this->team_name=name;}
    void setChannelList(QVector<IChannel*> channels) {this->channel_list=channels;}
    void setAssignmentList(QVector<IAssignment*> assignment_list) {this->assignment_list=assignment_list;}
    void setUserList(QVector<IUser*> users) {this->user_list=users;}
    void setAdminList(QVector<IUser*> admin_list) {this->admin_list=admin_list;}
    int getId() {return this->team_id;}
    virtual void setTeamPhoto(QString photo) {this->photo=photo;}
protected:
    int team_id;
    int creator_id;
    QString team_name;
    QString photo;
    QVector<IChannel*> channel_list;
    QVector<IAssignment*> assignment_list;
    QVector<IUser*> user_list;
    QVector<IUser*> admin_list;
};

#endif // ATEAM_H
