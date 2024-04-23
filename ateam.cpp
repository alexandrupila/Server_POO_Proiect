#include "ateam.h"
#include <QJsonArray>

ATeam::ATeam() {}

//TO DO: Serializarea pentru un assignment de adaugat
#include "user.h"

QJsonDocument ATeam::serialize()
{
    QJsonObject jsonObj;

    jsonObj["team_id"]=this->team_id;
    jsonObj["team_name"]=this->team_name;

    QJsonArray channelsObj;
    for(AChannel* channel_it:channel_list)
    {
        channelsObj.append(channel_it->serialize().object());
    }
    jsonObj["channels"]=channelsObj;

    QJsonArray assignmentsObj;
    for(AAssignment* assignment_it:assignment_list)
    {
        assignmentsObj.append(assignment_it->serialize().object());
    }
    jsonObj["assignment_list"]=assignmentsObj;

    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

void ATeam::deserialize(QJsonObject &receivedObj)
{

}
