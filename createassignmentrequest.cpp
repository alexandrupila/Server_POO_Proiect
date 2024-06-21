#include "createassignmentrequest.h"

CreateAssignmentRequest::CreateAssignmentRequest() {}

void CreateAssignmentRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();

    IResponse* resp=nullptr;

    if(qh.isAdmin(user_id,team_id))
    {
        IAssignment* assign=new Assignment;
        assign->deserialize(request);

        int assignment_id=qh.createAssignment(assign);

        QJsonObject jsonObj=qh.retrieveSpecificAssignment(assignment_id)->serialize().object();

        resp=new OkResponse(jsonObj,"create assigment");

    }
    else
    {
        resp=new ErrorResponse();
    }

    resp->sendResponse(clientSocket);
}
