#ifndef TEAM_H
#define TEAM_H

#include "ateam.h"

class Team : public ATeam
{
public:
    Team();
    Team(int creator_id,QString team_name,int team_id=-1);
    QJsonDocument serialize();
    void deserialize(QJsonObject& receivedObj);
    Team(const Team& other);
};

#endif // TEAM_H
