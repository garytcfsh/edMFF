#ifndef MODIFYDEFINITIONFILE_H
#define MODIFYDEFINITIONFILE_H

#include "modifyfile.h"
#include "face.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <math.h>

class ModifyDefinitionFile : public ModifyFile
{
public:
    ModifyDefinitionFile();

    void writeFile( QString, QList<Face>*, float, float, int);
};

#endif // MODIFYDEFINITIONFILE_H
