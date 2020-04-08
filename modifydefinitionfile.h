#ifndef MODIFYDEFINITIONFILE_H
#define MODIFYDEFINITIONFILE_H

#include "modifyfile.h"
#include "face.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ModifyDefinitionFile : public ModifyFile
{
public:
    ModifyDefinitionFile();

    void writeFile( QString, QList<Face>*, float);
};

#endif // MODIFYDEFINITIONFILE_H
