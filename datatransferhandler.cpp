#include "datatransferhandler.h"
#include "logger.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "loginrequest.h"
#include "registerrequest.h"
#include "updateprofilerequest.h"
#include "createdirectmessagechatrequest.h"
#include "creategroupchatrequest.h"
#include "chatsrequest.h"
#include "sendmessagerequest.h"
#include "exception.h"
#include "addteammemberrequest.h"
#include "createteamrequest.h"
#include "leavedirectchatrequest.h"
#include "leavegroupchatrequest.h"
#include "specificchatrequest.h"
#include "addusertochatrequest.h"
#include "removeuserfromchatrequest.h"
#include "teamsrequest.h"
#include "specificteamrequest.h"
#include "chatuserlistrequest.h"
#include "deletegrouprequest.h"
#include "removeuserfromteamrequest.h"
#include "createchannelrequest.h"
#include "channelrequest.h"
#include "createassignmentrequest.h"
#include "changeprofilephotorequest.h"
#include "filerequest.h"
#include "addsubmissionrequest.h"
#include "assignmentsrequest.h"
#include "submissionsrequest.h"
#include "specificassignmentrequest.h"
#include "sendmessagechannelrequest.h"
#include "channelfilerequest.h"
#include "gradesubmissionrequest.h"
#include "changeteamphotorequest.h"
#include "teamuserlistrequest.h"
#include "adminlistrequest.h"
#include "emptyrequest.h"
#include "addadminrequest.h"
#include "leaveteamrequest.h"


DataTransferHandler::DataTransferHandler()
{
    this->timer_repeated_request=nullptr;
    this->repeatedRequest=new EmptyRequest;
}

DataTransferHandler::DataTransferHandler(QTcpSocket* socket)
{
    this->clientSocket=socket;
    this->timer_repeated_request=nullptr;
    this->repeatedRequest=new EmptyRequest;
}

void DataTransferHandler::stopTimer()
{
    if (this->timer_repeated_request==nullptr) return;
    if(this->timer_repeated_request->isActive())
    {
        this->timer_repeated_request->stop();
        disconnect(timer_repeated_request,&QTimer::timeout,this,&DataTransferHandler::repeatRequest);

    }
    this->repeatedRequest=new EmptyRequest;
}

void DataTransferHandler::initRepeatableRequest(IRequest *req,QJsonObject jsonObj)
{
    repeatedRequest=req;
    this->lastRequest=jsonObj;
    if(this->timer_repeated_request==nullptr)
    {
       this->timer_repeated_request=new QTimer(this);
       timer_repeated_request->setInterval(3000);
    }
    else
    {
        if(!this->timer_repeated_request->isActive())
        {
            timer_repeated_request->setInterval(3000);
        }
    }
    connect(timer_repeated_request,&QTimer::timeout,this,&DataTransferHandler::repeatRequest);
    timer_repeated_request->start();
}

void DataTransferHandler::readClientData()
{
    QByteArray data = clientSocket->readAll();

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);

    try
    {
        if(error.error!=QJsonParseError::NoError)
        {
            Exception exceptie("Error parsing JSON");
            qDebug()<<data;
            qDebug()<<error.errorString();
            exceptie.raise();
        }
    }
    catch(Exception& exceptie)
    {
        Logger::logError(exceptie.what());
        return;
    }

    QJsonObject jsonObj;

    if (jsonDoc.isObject()) {
        jsonObj = jsonDoc.object();


        qDebug() << "Received JSON:" << jsonObj;
    } else {
        qDebug() << "Received data is not JSON object.";
        return;
    }

    IRequest* receivedRequest;

    if(jsonObj.value("request_type")=="register")
    {
        receivedRequest=new RegisterRequest;
    }
    else if(jsonObj.value("request_type")=="login")
    {
        receivedRequest=new LoginRequest;
    }
    else if(jsonObj.value("request_type")=="update_profile")
    {
        receivedRequest= new UpdateProfileRequest;
    }
    else if(jsonObj.value("request_type")=="create direct_chat")
    {
        receivedRequest=new CreateDirectMessageChatRequest;
    }
    else if(jsonObj.value("request_type")=="create group_chat")
    {
        receivedRequest=new CreateGroupChatRequest;
    }
    else if(jsonObj.value("request_type")=="chaturi")
    {
        stopTimer();
        receivedRequest=new ChatsRequest;
    }
    else if(jsonObj.value("request_type")=="direct_chat" or jsonObj.value("request_type")=="group_chat")
    {
        stopTimer();
        receivedRequest=new SpecificChatRequest;
        initRepeatableRequest(new SpecificChatRequest,jsonObj);
    }
    else if(jsonObj.value("request_type")=="sterge grup")
    {
        receivedRequest=new DeleteGroupRequest;
    }
    else if(jsonObj.value("request_type")=="adauga membru")
    {
        receivedRequest=new AddUserToChatRequest;
    }
    else if(jsonObj.value("request_type")=="send_message")
    {
        receivedRequest=new SendMessageRequest;
    }
    else if(jsonObj.value("request_type")=="send_message channel")
    {
        receivedRequest=new SendMessageChannelRequest;

        ////////////
    }
    else if(jsonObj.value("request_type")=="channel_file")
    {

        receivedRequest=new ChannelFileRequest;
            ///de facut requestul
    }
    else if(jsonObj.value("request_type")=="paraseste direct_chat")
    {
        receivedRequest=new LeaveDirectChatRequest;
    }
    else if(jsonObj.value("request_type")=="paraseste group_chat")
    {
        receivedRequest=new LeaveGroupChatRequest;
    }
    else if(jsonObj.value("request_type")=="remove user")
    {
        receivedRequest=new RemoveUserFromChatRequest;
    }
    else if(jsonObj.value("request_type")=="user_list")
    {
        receivedRequest=new ChatUserListRequest;
    }
    else if(jsonObj.value("request_type")=="user_list_for_team")
    {
        //toti membrii non admini
        receivedRequest=new TeamUserListRequest;
    }
    else if (jsonObj.value("request_type")=="admin_list_for_team")
    {
        receivedRequest=new AdminListRequest;
    }
    else if(jsonObj.value("request_type")=="teams")
    {
        stopTimer();
        receivedRequest=new TeamsRequest;
    }
    else if(jsonObj.value("request_type")=="team")
    {
        receivedRequest=new SpecificTeamRequest;
    }
    else if(jsonObj.value("request_type")=="create team")
    {
        receivedRequest=new CreateTeamRequest;
    }
    else if(jsonObj.value("request_type")=="adauga membru_in_team")
    {
        receivedRequest=new AddTeamMemberRequest;
    }
    else if(jsonObj.value("request_type")=="remove user_from_team")
    {
        receivedRequest=new RemoveUserFromTeamRequest;
    }
    else if(jsonObj.value("request_type")=="create_channel")
    {
        receivedRequest=new CreateChannelRequest;
    }
    else if(jsonObj.value("request_type")=="channel")
    {
        stopTimer();
        receivedRequest=new ChannelRequest;
        initRepeatableRequest(new ChannelRequest,jsonObj);
    }
    else if(jsonObj.value("request_type")=="create assigment")
    {
        receivedRequest= new CreateAssignmentRequest;
    }
    else if(jsonObj.value("request_type")=="assigments")
    {
        receivedRequest= new AssignmentsRequest;
    }
    else if(jsonObj.value("request_type")=="change_photo_profile")
    {
        receivedRequest=new ChangeProfilePhotoRequest;
    }
    else if(jsonObj.value("request_type")=="open chat_file")
    {
        receivedRequest=new FileRequest;
    }
    else if(jsonObj.value("request_type")=="assigment_file")
    {
        receivedRequest=new AddSubmissionRequest;
    }
    else if(jsonObj.value("request_type")=="????????")
    {
        receivedRequest=new SubmissionsRequest;
    }
    else if(jsonObj.value("request_type")=="assigment")
    {
        receivedRequest=new SpecificAssignmentRequest;
    }
    else if(jsonObj.value("request_type")=="grade_submission")
    {
        receivedRequest=new GradeSubmissionRequest;
    }
    else if(jsonObj.value("request_type")=="change_team_photo")
    {
        receivedRequest=new ChangeTeamPhotoRequest;
    }
    else if(jsonObj.value("request_type")=="adauga admin_in_team")
    {
        receivedRequest=new AddAdminRequest;
    }
    else if(jsonObj.value("request_type")=="paraseste_team")
    {
        receivedRequest=new LeaveTeamRequest;
    }

    else return;

    QueryHandler& qh=QueryHandler::getInstance();
    qh.connectDB();
    receivedRequest->processRequest(jsonObj,clientSocket);
    qh.disconnectDB();
}

void DataTransferHandler::sendDataToClient(const QByteArray &data)
{
    qDebug()<<"sending data to client "<<clientSocket->socketDescriptor();
    clientSocket->write(data);
}

void DataTransferHandler::repeatRequest()
{
    if(dynamic_cast<EmptyRequest*>(this->repeatedRequest)==nullptr)
    {
        QueryHandler& qh=QueryHandler::getInstance();
        qh.connectDB();
        this->repeatedRequest->processRequest(this->lastRequest,clientSocket);
        qh.disconnectDB();
    }

}
