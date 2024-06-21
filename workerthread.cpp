#include "workerthread.h"
#include <QTcpSocket>
#include "logger.h"
#include "datatransferhandler.h"
#include "queryhandler.h"

WorkerThread::WorkerThread(QObject *parent)
    : QObject{parent}
{}

void WorkerThread::process()
{
    Logger::logGeneral("New thread started.");
    clientSocket=new QTcpSocket();
    clientSocket->setSocketDescriptor(m_socketDescriptor);
    QueryHandler & qh=QueryHandler::getInstance();
    qh.setConnNr(m_socketDescriptor);
    Logger::logConnection("New connection on socket descriptor "+QString::number(m_socketDescriptor));

    emit clientConnected(clientSocket);

    this->datahandler=new DataTransferHandler(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &WorkerThread::readClientData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &WorkerThread::handleDisconnect);
}

void WorkerThread::readClientData() {
    this->datahandler->readClientData();
}

void WorkerThread::handleDisconnect() {
    delete this->datahandler;
    emit clientDisconnected();
}
