#ifndef STOREMFFNODEONREGIONFACE_H
#define STOREMFFNODEONREGIONFACE_H

#include "searchnodeonregionface.h"
#include <QTextStream>
#include <QDebug>
#include <math.h>

class StoreMffNodeOnRegionFace : public SearchNodeOnRegionFace
{
public:
    StoreMffNodeOnRegionFace();

    void storeNodeOnRegionFace(QString, QList<Face> *, float, float);
};

#endif // STOREMFFNODEONREGIONFACE_H
