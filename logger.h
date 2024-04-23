#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger& getInstance();
    static void destroyInstance();
    static void logConnection(QString message);
    static void logGeneral(QString message);
    static void logIncomingRequest(QString message);
protected:
    static QString logfilepath;
    static Logger* instance;
    explicit Logger(QObject *parent = nullptr);
    static void logToFile(QString message);
    void createLogsDirectory();
    ~Logger() {}

signals:
};

#endif // LOGGER_H
