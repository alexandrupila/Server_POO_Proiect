#include "logger.h"
#include "QDebug"
#include "QTime"
#include "QFile"
#include "QTextStream"
#include "QDir"

Logger* Logger::instance=nullptr;
QString Logger::logfilepath="NULL";

Logger &Logger::getInstance()
{
    if(instance==nullptr)
    {
        instance=new Logger;
    }
    return *instance;
}

void Logger::destroyInstance()
{
    if(instance==nullptr) return;
    else
    {
        delete instance;
        instance=nullptr;
    }

}

void Logger::logConnection(QString message)
{
    QString logMessage="[NEW CONNECTION] "+message;
    qDebug()<<logMessage;
    logToFile(logMessage);
}

void Logger::logGeneral(QString message)
{
    QString logMessage="[OTHERS] "+message;
    qDebug()<<logMessage;
    logToFile(logMessage);
}

void Logger::logIncomingRequest(QString message)
{
    QString logMessage="[Incoming Request] "+message;
    qDebug()<<logMessage;
    logToFile(logMessage);
}

void Logger::logError(QString message)
{
    QString logMessage="[ERROR]" +message;
    qDebug()<<logMessage;
    logToFile(logMessage);
}

Logger::Logger(QObject *parent)
    : QObject{parent}
{

}

void Logger::logToFile(QString message)
{
    QDateTime date=QDateTime::currentDateTime();
    QString formattedTime= date.toString("dd-MM-yyyy_hh-mm-ss");

    QString logsDirectoryPath="Logs";

    QDir dir;
    if(!dir.exists(logsDirectoryPath))
    {
        if(dir.mkdir(logsDirectoryPath))
        {
            qDebug()<<"Logs directory created succesfully.";
        }
        else
        {
            qDebug()<<"Failed to create logs directory";
            return;
        }
    }

    if(logfilepath=="NULL")
    {
        logfilepath=logsDirectoryPath+QDir::separator()+"LOGS_"+formattedTime+".txt";

        QFile logfile(logfilepath);
        if(logfile.open(QIODevice::WriteOnly))
        {
            qDebug()<<"Log file created succesfully.";

            logfile.close();
        }
        else
        {
            qDebug()<<"Failed to create file.";
        }
    }

    QFile logfile(logfilepath);

    if(!logfile.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug()<<"Failed to open file for appending:"<<logfile.errorString();
        return;
    }

    QTextStream out(&logfile);

    out<<message<<"\n";

    logfile.close();
}
