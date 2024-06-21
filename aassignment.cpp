#include "aassignment.h"

AAssignment::AAssignment() {}

int AAssignment::getCreatorId()
{
    return this->creator_id;
}

int AAssignment::getTeamId()
{
    return this->team_id;
}

QString AAssignment::getAssignmentName()
{
    return this->assignment_name;
}

QString AAssignment::getDescription()
{
    return this->description;
}

QDate AAssignment::getDate()
{
    return this->due_date;
}

