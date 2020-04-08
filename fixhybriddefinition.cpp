#include "fixhybriddefinition.h"

FixHybridDefinition::FixHybridDefinition()
{
    //merge file
    qDebug()<< "dfn definition file (.mff)";
    QTextStream d( stdin);
    QString dfnPath = d.readLine();
    qDebug()<< "hybrid definition file (.mff)";
    QTextStream h( stdin);
    QString hybridPath = h.readLine();
    mergefile = new DFN2Hybrid();
    mergefile->merge( dfnPath, hybridPath);

    //read region file
    QString regionPath;
    qDebug()<< "select input region type: 1. box_region 2. slab_region" << endl;
    QTextStream s( stdin);
    QString regionType = s.readLine();
    if (regionType == "1")
        inputBoundaryRegion = new BoxRegion();
    else if (regionType == "2")
        inputBoundaryRegion = new SlabRegion();
    else
    {
        qDebug()<< "region type error" << endl;
        exit(2);
    }
    qDebug()<< "region file (.sab): ";
    QTextStream sr( stdin);
    regionPath = sr.readLine();
    inputBoundaryRegion->setRegionFace( regionPath, regionFace);

    //change boundary condition of nodes
    disError = 1;
    degError = 1;
    hybridPath = hybridPath + "merge";
    searchNodeOnRegionFace = new StoreDefinitionFileNodeOnRegionFace();
    searchNodeOnRegionFace->storeNodeOnRegionFace( hybridPath, regionFace, disError, degError);

    //write file
    modifyFile = new ModifyDefinitionFile();
    modifyFile->writeFile( hybridPath, regionFace, disError);

}
