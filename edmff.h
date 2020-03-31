#ifndef EDMFF_H
#define EDMFF_H

#include "inputboundaryregion.h"
#include "searchnodeonregionface.h"
#include "modifydefinitionfile.h"
#include "mergefile.h"
#include "face.h"
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <QDebug>


class EdMff
{
public:
    EdMff();

protected:
    InputBoundaryRegion *inputBoundaryRegion;
    SearchNodeOnRegionFace *searchNodeOnRegionFace;
    ModifyDefinitionFile *modifyDefinitionFile;
    MergeFile *mergefile;
    QList< Face> *regionFace;
    float disError, degError;

};

#endif // EDMFF_H
