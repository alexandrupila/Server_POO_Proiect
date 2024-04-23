#ifndef ATEAM_H
#define ATEAM_H

#include "iteam.h"
#include "achannel.h"
#include "aassignment.h"
#include <QVector>
class ATeam : public ITeam
{
public:
    ATeam();
    QJsonDocument serialize();
    void deserialize(QJsonObject& receivedObj);
protected:
    int team_id;
    QString team_name;
    QVector<AChannel*> channel_list;
    QVector<AAssignment*> assignment_list;
};

#endif // ATEAM_H
