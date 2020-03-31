#ifndef INPUTBOUNDARYREGION_H
#define INPUTBOUNDARYREGION_H

#include "face.h"
#include <QStringList>
#include <QTextStream>
#include <QDebug>


class InputBoundaryRegion
{
public:
    InputBoundaryRegion();
    virtual ~InputBoundaryRegion(){}

    virtual void setRegionFace( QString, QList< Face>*){}
};

#endif // INPUTBOUNDARYREGION_H
