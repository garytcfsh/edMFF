#include "fixhybriddefinition.h"

FixHybridDefinition::FixHybridDefinition()
{
    qDebug()<< endl << "dfn definition file (.mff)";
    QTextStream d( stdin);
    dfnPath = d.readLine();
    qDebug()<< endl << "hybrid definition file (.mff)";
    QTextStream h( stdin);
    hybridPath = h.readLine();

    //read region file
    QString regionType = readRegion();
    if (regionType == "box")
        inputBoundaryRegion = new BoxRegion();
    else if (regionType == "slab")
        inputBoundaryRegion = new SlabRegion();
    else
    {
        qDebug()<< "Exit: region type error" << endl;
        exit(1);
    }
    inputBoundaryRegion->setRegionFace( regionPath, regionFace);

    //merge file
    mergefile = new DFN2Hybrid();
    int dfnFracNodeNum = mergefile->merge( dfnPath, hybridPath);

    //change boundary condition of nodes
    disError = 1;
    degError = 1;
    hybridPath = hybridPath + "merge";
    searchNodeOnRegionFace = new StoreDefinitionFileNodeOnRegionFace();
    searchNodeOnRegionFace->storeNodeOnRegionFace( hybridPath, regionFace, disError, degError);

    //write file
    modifyFile = new ModifyDefinitionFile();
    modifyFile->writeFile( hybridPath, regionFace, disError, degError, dfnFracNodeNum);

}
