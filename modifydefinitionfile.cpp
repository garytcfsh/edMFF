#include "modifydefinitionfile.h"

ModifyDefinitionFile::ModifyDefinitionFile()
{

}

void ModifyDefinitionFile::writeFile( QString hybridPath, QList< Face> *region, float disError)
{
    qDebug()<< "writing file...";

    QFile fileIn, fileOut;
    QTextStream streamIn, streamOut;
    QString oneLine;
    QStringList sl;

    fileIn.setFileName( hybridPath);
    fileIn.open( QFile::ReadOnly|QFile::Text);
    streamIn.setDevice( &fileIn);

    QString newPath = hybridPath;
    newPath.remove( newPath.indexOf( ".") + 1, newPath.length() - newPath.indexOf( "."));
    newPath = newPath + "mffnew";
    fileOut.setFileName( newPath);
    fileOut.open( QFile::WriteOnly|QFile::Text);
    streamOut.setDevice( &fileOut);

    //write file
    //write header
    int customizedGroup = -1;
    Node node;
    float dis = -1;
    int num;
    while (!oneLine.contains("NODE"))
    {
        oneLine = streamIn.readLine();
        if (oneLine.contains("custom"))
        {
            sl = oneLine.simplified().split(" ");
            customizedGroup = sl[3].remove(":").toInt();
        }
        streamOut << oneLine << endl;
    }
    //write nodes
    sl = oneLine.simplified().split(" ");
    while (sl[0] != "0")
    {
        oneLine = streamIn.readLine();
        sl = oneLine.simplified().split(" ");
        node.setNode( sl[1].toFloat(), sl[2].toFloat(), sl[3].toFloat());

        //only change customized boundary
// I can't set customized boundary group on inner region,
// cos inner boundary region will cut things off which in the region
//        if (sl[7].toInt() == customizedGroup && customizedGroup != -1)
        {
            //check nodes are on the plane or not
            //in fracture simulation, if a node is on the plane, it should be in the area
            for (int i=0; i<region->count(); i++)//for each faces
            {
                dis = node.xyz.distanceToPlane( (*region)[i].getApex()[0].xyz, (*region)[i].getApex()[1].xyz, (*region)[i].getApex()[2].xyz);
                if (dis < disError && dis > -disError)//on the plane
                {
                    if ((*region)[i].getNodeOnFace().count() != 0)//on the face
                    {
                        num = (*region)[i].findNearestNode( node);
                        sl[4] = "0";//set connected type
                        sl[7].setNum( -num);//set connected group
                        qDebug()<<-num;

                    }else//on the null face
                    {
                        sl[4] = "0";//cancle const boundary head type on the null face
                        sl[7] = "0";
                    }

                    oneLine = "";
                    for (int j=0; j<sl.count(); j++)
                        oneLine = oneLine + '\t' + sl[j];
                }
            }
        }

        streamOut << oneLine << endl;
    }
    //write configuration
    while (!streamIn.atEnd())
    {
        oneLine = streamIn.readAll();
        streamOut << oneLine << endl;
    }

    qDebug()<< "complete" << endl
            << fileOut.fileName() << " is created";
}
