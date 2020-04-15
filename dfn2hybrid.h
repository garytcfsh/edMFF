#ifndef DFN2HYBRID_H
#define DFN2HYBRID_H

#include "mergefile.h"
#include "boundarycondition.h"

class DFN2Hybrid : public MergeFile
{
public:
    DFN2Hybrid();

    int merge(QString, QString);

    QList< BoundaryCondition> fracBD, hybridBD;
};

#endif // DFN2HYBRID_H
