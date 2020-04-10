/*
 * determine if the nodes are within the area
 * change boundary type and group number of nodes in the area
 * write new file
*/
#include "modifydefinitionfile.h"

const float pi = 3.1415926;

ModifyDefinitionFile::ModifyDefinitionFile()
{

}

void ModifyDefinitionFile::writeFile( QString hybridPath, QList< Face> *regionFace, float disError, float degError)
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
    QVector3D a, b;
    float aDis, bDis, degree = 0;
    float dis = -1;
    int num;
    while (!oneLine.contains("NODE"))
    {
        oneLine = streamIn.readLine();
        if (oneLine.contains("custom"))//get custom boundary group number
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

//        if (sl[7].toInt() == customizedGroup && customizedGroup != -1)
        for (int i=0; i<regionFace->count(); i++)//for each faces
        {
            dis = node.xyz.distanceToPlane( (*regionFace)[i].getApex()[0].xyz, (*regionFace)[i].getApex()[1].xyz, (*regionFace)[i].getApex()[2].xyz);
            if (dis < disError && dis > -disError)//on the plane
            {
                //only handle convex polygon
                //check whether nodes are in the area or not
                degree = 0;
                int j, k, number = (*regionFace)[i].getApex().count();
                for (j=0, k=number-1; j<number; k=j++)//add degree of all apex
                {
                    a = (*regionFace)[i].getApex()[j].xyz;
                    b = (*regionFace)[i].getApex()[k].xyz;
                    aDis = node.xyz.distanceToPoint( a);
                    bDis = node.xyz.distanceToPoint( b);
                    if (aDis*bDis == 0)//on the apex
                    {
                        degree = 360;
                        j = number;
                    }
                    else
                        degree = degree + (acos( a.dotProduct( a-node.xyz, b-node.xyz) / (aDis * bDis)) * 180 / pi);
                }

                //change nodes properties which are in the area
                if ( (degree <= 360+degError && degree >= 360-degError))//in the area -> store
                {
                    if ((*regionFace)[i].getNodeOnFace().count() != 0)//on the face
                    {
                        num = (*regionFace)[i].findNearestNode( node);
                        sl[4] = "0";//set connected type
                        sl[7].setNum( -num);//set connected group
                    } else//on the null face
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

    qDebug() << "complete" << endl
            << fileOut.fileName() << " is created";
}
