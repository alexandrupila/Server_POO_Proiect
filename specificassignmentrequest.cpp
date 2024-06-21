#include "specificassignmentrequest.h"
#include "isubmission.h"

SpecificAssignmentRequest::SpecificAssignmentRequest() {}

void SpecificAssignmentRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();
    int assignment_id=request["assigment_id"].toInt();

    IAssignment* assign=qh.retrieveSpecificAssignment(assignment_id);

    QJsonObject serialized_assignment=assign->serialize().object();

    if(qh.isAdmin(user_id,team_id))
    {
        serialized_assignment["request_type"]="assigment_admin";
    }
    else
    {
        serialized_assignment["request_type"]="assigment_membru";
        ISubmission* subm=qh.retrieveSubmissionByID(user_id,assignment_id);
        serialized_assignment["nota"]=subm->getGrade();

    }

    QJsonDocument jsonDoc(serialized_assignment);

    DataTransferHandler* datahandler=new DataTransferHandler(clientSocket);
    datahandler->sendDataToClient(jsonDoc.toJson());

    //RASPUNS DE FACUT
}
