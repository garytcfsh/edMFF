#ifndef MERGEFILE_H
#define MERGEFILE_H

#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QDebug>

class MergeFile
{
public:
    MergeFile();
    virtual ~MergeFile(){}

    virtual void merge(QString, QString){}
};

#endif // MERGEFILE_H
