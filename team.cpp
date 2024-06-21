#include "team.h"
#include <QJsonArray>

Team::Team() {}

Team::Team(int creator_id, QString team_name, int team_id)
{
    this->creator_id=creator_id;
    this->team_name=team_name;
    this->team_id=team_id;
}

//TO DO: Serializarea pentru un assignment de adaugat

QJsonDocument Team::serialize()
{
    QJsonObject jsonObj;

    jsonObj["team_id"]=this->team_id;
    jsonObj["team_name"]=this->team_name;
    jsonObj["creator_id"]=this->creator_id;

    QJsonArray channelsObj;
    for(IChannel* channel_it:channel_list)
    {
        channelsObj.append(channel_it->serialize().object());
    }
    jsonObj["channels"]=channelsObj;

    QJsonArray assignmentsObj;
    for(auto assignment_it:assignment_list)
    {
        assignmentsObj.append(assignment_it->serialize().object());
    }
    jsonObj["assignment_list"]=assignmentsObj;

    QJsonArray usersObj;
    for(auto user_it:user_list)
    {
        usersObj.append(user_it->serialize().object());
    }
    jsonObj["user_list"]=usersObj;

    QJsonArray adminsObj;
    for(auto admin_it:admin_list)
    {
        adminsObj.append(admin_it->serialize().object());
    }

    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

void Team::deserialize(QJsonObject &receivedObj)
{

}

Team::Team(const Team &other)
{
    this->team_id=other.team_id;
    this->team_name=other.team_name;
    this->creator_id=other.creator_id;

    for(IChannel* ch_it:other.channel_list)
    {
        this->channel_list.append(ch_it);
    }
    for(auto assig_it:other.assignment_list)
    {
        this->assignment_list.append(assig_it);
    }
    for(auto user_it:other.user_list)
    {
        this->user_list.append(user_it);
    }
    for(auto admin_it:other.admin_list)
    {
        this->admin_list.append(admin_it);
    }
}


