#ifndef AFILE_H
#define AFILE_H

#include "ifile.h"

class AFile : public IFile
{
public:
    AFile() {};
protected:
    QString filename;
    QString filecontent;
};

#endif // AFILE_H
