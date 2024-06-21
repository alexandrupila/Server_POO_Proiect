#include "file.h"

File::File(QString filename, QString filecontent)
{
    this->filename=filename;
    this->filecontent=filecontent;
}

QJsonDocument File::serialize()
{
    QJsonObject jsonObj;

    jsonObj["filename"]=this->filename;
    jsonObj["file_content"]=this->filecontent;

    QJsonDocument jsonDoc(jsonObj);

    return jsonDoc;
}

void File::deserialize(QJsonObject &receivedObj)
{

}
