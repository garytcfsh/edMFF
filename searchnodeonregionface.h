#ifndef SEARCHNODEONREGIONFACE_H
#define SEARCHNODEONREGIONFACE_H

#include "face.h"
#include <QStringList>
#include <QTextStream>
#include <math.h>
#include <QDebug>

class SearchNodeOnRegionFace
{
public:
    SearchNodeOnRegionFace();
    virtual ~SearchNodeOnRegionFace(){}

    virtual void storeNodeOnRegionFace(QString, QList< Face>*, float, float){}
};

#endif // SEARCHNODEONREGIONFACE_H
