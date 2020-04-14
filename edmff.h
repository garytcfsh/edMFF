#ifndef EDMFF_H
#define EDMFF_H

#include "inputboundaryregion.h"
#include "searchnodeonregionface.h"
#include "modifyfile.h"
#include "mergefile.h"
#include "face.h"
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <QDebug>
#include <QFile>


class EdMff
{
public:
    EdMff();

    QString readRegion();

protected:
    InputBoundaryRegion *inputBoundaryRegion;
    SearchNodeOnRegionFace *searchNodeOnRegionFace;
    ModifyFile *modifyFile;
    MergeFile *mergefile;
    QList< Face> *regionFace;
    float disError, degError;
    QString dfnPath, hybridPath, regionPath;

};

#endif // EDMFF_H
