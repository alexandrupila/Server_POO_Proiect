#include "addsubmissionrequest.h"

AddSubmissionRequest::AddSubmissionRequest() {}

void AddSubmissionRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();
    int user_id=request["user_id"].toInt();
    int assig_id=request["assigment_id"].toInt();

    IResponse* resp;

    ISubmission* subm=new Submission();
    subm->deserialize(request);

    if(!qh.hasSubmitted(user_id,assig_id))
    {
        int subm_id=qh.addSubmission(user_id,assig_id,subm);

        subm=qh.retrieveSpecificSubmission(subm_id);

        if(subm_id==-1)
        {
            resp=new ErrorResponse();
        }
        else
        {
            resp=new OkResponse(subm->serialize().object(),"assigment_file"); //?????
        }
        resp->sendResponse(clientSocket);
    }

}
