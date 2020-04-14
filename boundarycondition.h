#ifndef BOUNDARYCONDITION_H
#define BOUNDARYCONDITION_H

#include <QStringList>

class BoundaryCondition
{
public:
    BoundaryCondition();

    void init( QString, QString, QString);
    QString getName();
    QString getGroup();
    QString getType();

private:
    QString name, group, type;
};

#endif // BOUNDARYCONDITION_H
