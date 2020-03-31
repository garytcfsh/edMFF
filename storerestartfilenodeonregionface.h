#ifndef STORERESTARTFILENODEONREGIONFACE_H
#define STORERESTARTFILENODEONREGIONFACE_H

#include "searchnodeonregionface.h"

class StoreRestartFileNodeOnRegionFace : public SearchNodeOnRegionFace
{
public:
    StoreRestartFileNodeOnRegionFace();

    void storeNodeOnRegionFace(QString, QList<Face> *, float, float);
};

#endif // STORERESTARTFILENODEONREGIONFACE_H
