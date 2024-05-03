#include "workerthread.h"
#include <QTcpSocket>
#include "logger.h"
#include "datatransferhandler.h"

WorkerThread::WorkerThread(QObject *parent)
    : QObject{parent}
{}

void WorkerThread::process()
{
    Logger::logGeneral("New thread started.");
    clientSocket=new QTcpSocket();
    clientSocket->setSocketDescriptor(m_socketDescriptor);
    Logger::logConnection("New connection on socket descriptor "+QString::number(m_socketDescriptor));
    // Add the socket to the list of clients
    emit clientConnected(clientSocket);

    // Connect signals/slots for reading data and handling disconnection

    connect(clientSocket, &QTcpSocket::readyRead, this, &WorkerThread::readClientData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &WorkerThread::handleDisconnect);
}

void WorkerThread::readClientData() {
    DataTransferHandler* datatransferhandler=new DataTransferHandler(clientSocket);
    datatransferhandler->readClientData();
}

void WorkerThread::handleDisconnect() {
    // Emit signal indicating client disconnection
    emit clientDisconnected();
    // Exit the thread event loop
}
