#include "boundarycondition.h"

BoundaryCondition::BoundaryCondition()
{

}

void BoundaryCondition::init(QString n, QString g, QString t)
{
    name = n;
    group = g;
    type = t;
}

QString BoundaryCondition::getName()
{
    return  name;
}

QString BoundaryCondition::getGroup()
{
    return  group;
}

QString BoundaryCondition::getType()
{
    return type;
}
