#include "fixhybriddefinition.h"

FixHybridDefinition::FixHybridDefinition()
{
    //merge file
    qDebug()<< endl << "dfn definition file (.mff)";
    QTextStream d( stdin);
    dfnPath = d.readLine();
    qDebug()<< endl << "hybrid definition file (.mff)";
    QTextStream h( stdin);
    hybridPath = h.readLine();

    //read region file
    qDebug()<< "select input region type: 1. box_region 2. slab_region";
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
    qDebug()<< endl << "region file (.sab): ";
    QTextStream sr( stdin);
    regionPath = sr.readLine();
    inputBoundaryRegion->setRegionFace( regionPath, regionFace);



}

void FixHybridDefinition::merge()
{
    mergefile = new DFN2Hybrid();
    mergefile->merge( dfnPath, hybridPath);
}

void FixHybridDefinition::changeBCofNodes()
{
    //change boundary condition of nodes
    disError = 1;
    degError = 1;
    hybridPath = hybridPath + "merge";
    searchNodeOnRegionFace = new StoreDefinitionFileNodeOnRegionFace();
    searchNodeOnRegionFace->storeNodeOnRegionFace( hybridPath, regionFace, disError, degError);

}

void FixHybridDefinition::writeFile()
{
    //write file
    modifyFile = new ModifyDefinitionFile();
    modifyFile->writeFile( hybridPath, regionFace, disError, degError);

}
