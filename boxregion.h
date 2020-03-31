#ifndef BOXREGION_H
#define BOXREGION_H

#include "inputboundaryregion.h"

class BoxRegion : public InputBoundaryRegion
{
public:
    BoxRegion();

    void setRegionFace(QString, QList< Face>*);
};

#endif // BOXREGION_H
