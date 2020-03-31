#ifndef DFN2HYBRID_H
#define DFN2HYBRID_H

#include "mergefile.h"

class DFN2Hybrid : public MergeFile
{
public:
    DFN2Hybrid();

    void merge(QString, QString);
};

#endif // DFN2HYBRID_H
