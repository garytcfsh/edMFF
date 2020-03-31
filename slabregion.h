#ifndef SLABREGION_H
#define SLABREGION_H

#include "inputboundaryregion.h"
#include <math.h>

class SlabRegion : public InputBoundaryRegion
{
public:
    SlabRegion();

    void setRegionFace(QString, QList< Face>*);
};

#endif // SLABREGION_H
