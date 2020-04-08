#ifndef MODIFYFILE_H
#define MODIFYFILE_H

#include "face.h"
#include <QStringList>

class ModifyFile
{
public:
    ModifyFile();
    virtual ~ModifyFile(){}

    virtual void writeFile( QString, QList< Face>*, float, float){}
};

#endif // MODIFYFILE_H
