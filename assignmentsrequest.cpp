#include "assignmentsrequest.h"

AssignmentsRequest::AssignmentsRequest() {}

void AssignmentsRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();

    QVector<IAssignment*> assignments=qh.retrieveAssignments(team_id);

    QJsonObject obj;
    QJsonArray assignments_array;

    for(auto assign_it: assignments)
    {
        QJsonObject chat_obj=assign_it->serialize().object();
        assignments_array.append(chat_obj);
    }

    obj["assigments"]=assignments_array;

    obj["request_type"]="assigments";

    QJsonDocument jsonDoc(obj);

    DataTransferHandler* transferHandler=new DataTransferHandler(clientSocket);
    transferHandler->sendDataToClient(jsonDoc.toJson());

}
