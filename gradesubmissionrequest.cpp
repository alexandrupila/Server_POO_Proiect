#include "gradesubmissionrequest.h"

GradeSubmissionRequest::GradeSubmissionRequest() {}

void GradeSubmissionRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{

    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int submission_id=request["submission_id"].toInt();
    int team_id; //DE FACUT QUERY SA VAD IN CE TEAM ESTE
    int grade=request["nota"].toInt();

    ISubmission* subm=qh.retrieveSpecificSubmission(submission_id);

    IResponse* resp;

    // if(!qh.isAdmin(user_id,team_id) or qh.isGraded(submission_id) or subm->getUserId()==user_id)
    // {
    //     resp=new ErrorResponse();
    // }
    QJsonObject obj;
     if(qh.isGraded(submission_id) or subm->getUserId()==user_id)
     {
        //resp=new ErrorResponse();
        obj["situation"]="nu exista";
     }
    else
    {
        obj["situation"]="exista";
        qh.gradeSubmission(submission_id,grade);            //"situatio":"exista"
        //resp=new OkResponse("grade_submission"); //
    }

     resp=new OkResponse(obj,"grade_submission");
    resp->sendResponse(clientSocket);
}
