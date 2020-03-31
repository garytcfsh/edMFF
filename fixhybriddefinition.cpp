#include "fixhybriddefinition.h"

FixHybridDefinition::FixHybridDefinition()
{
//    QString regionPath, definitionPath;
//    qDebug()<< "select input region type: 1. box_region 2. slab_region" << endl;
//    QTextStream s( stdin);
//    QString regionType = s.readLine();
//    if (regionType == "1")
//        inputBoundaryRegion = new BoxRegion();
//    else if (regionType == "2")
//        inputBoundaryRegion = new SlabRegion();
//    else
//    {
//        qDebug()<< "region type error" << endl;
//        exit(2);
//    }
//    qDebug()<< "region file (.sab): ";
//    QTextStream sr( stdin);
//    regionPath = sr.readLine();
//    inputBoundaryRegion->setRegionFace( regionPath, regionFace);
//    qDebug()<< "preliminary head file (restart.mff): ";
//    QTextStream s1( stdin);
//    QString restartPath = s1.readLine();
//    searchNodeOnRegionFace = new StoreRestartFileNodeOnRegionFace();
//    searchNodeOnRegionFace->storeNodeOnRegionFace( restartPath, regionFace, disError, degError);

    QTextStream d( stdin);
    QString dfnPath = d.readLine();
    QTextStream h( stdin);
    QString hybridPath = h.readLine();
    mergefile = new DFN2Hybrid();
    mergefile->merge( dfnPath, hybridPath);
}
