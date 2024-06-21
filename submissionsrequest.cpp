#include "submissionsrequest.h"

SubmissionsRequest::SubmissionsRequest() {}

void SubmissionsRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int assig_id=request["assigment_id"].toInt();

    QVector<ISubmission*> submissions=qh.retrieveSubmissions(assig_id);

    QJsonObject obj;
    QJsonArray submArray;

    for(auto subm_it: submissions)
    {
        QJsonObject subm_obj=subm_it->serialize().object();
        submArray.append(subm_obj);
    }

    obj["submissions"]=submArray;
    obj["request_type"]="submissions";

    QJsonDocument doc(obj);

    //TODO: Cu datatransferhandler si cu response

    DataTransferHandler* transferHandler=new DataTransferHandler(clientSocket);
    transferHandler->sendDataToClient(doc.toJson());
}
