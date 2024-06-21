#ifndef ITEAM_H
#define ITEAM_H

#include "iserializable.h"
#include "ichannel.h"
#include "iassignment.h"

class ITeam : public ISerializable
{
public:
    ITeam();
    virtual void setId(int id) = 0;
    virtual void setCreator_id(int id) = 0;
    virtual void setTeamName(QString name) = 0;
    virtual void setChannelList(QVector<IChannel*> channels) = 0;
    virtual void setAssignmentList(QVector<IAssignment*> assignment_list) = 0;
    virtual void setUserList(QVector<IUser*> users) = 0;
    virtual void setAdminList(QVector<IUser*> admin_list) = 0;
    virtual int getId() = 0;
    virtual void setTeamPhoto(QString photo)=0;
};

#endif // ITEAM_H
