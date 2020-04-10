//node on face store complete
//to-do
//merge pure dfn file and hybrid file
//(copy frac node from dfn to hybrid)
//(copy frac elem from dfn to hybrid)
#ifndef FIXHYBRIDDEFINITION_H
#define FIXHYBRIDDEFINITION_H

#include "edmff.h"
#include "boxregion.h"
#include "slabregion.h"
#include "storedefinitionfilenodeonregionface.h"
#include "storerestartfilenodeonregionface.h"
#include "dfn2hybrid.h"
#include "modifydefinitionfile.h"
#include <QDebug>

class FixHybridDefinition : public EdMff
{
public:
    FixHybridDefinition();
};

#endif // FIXHYBRIDDEFINITION_H
