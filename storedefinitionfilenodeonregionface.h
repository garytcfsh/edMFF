#ifndef STOREDEFINITIONFILENODEONREGIONFACE_H
#define STOREDEFINITIONFILENODEONREGIONFACE_H

#include "searchnodeonregionface.h"

class StoreDefinitionFileNodeOnRegionFace : public SearchNodeOnRegionFace
{
public:
    StoreDefinitionFileNodeOnRegionFace();

    void storeNodeOnRegionFace(QString, QList<Face> *, float, float);
};

#endif // STOREDEFINITIONFILENODEONREGIONFACE_H
