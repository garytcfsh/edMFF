#include "storedefinitionfilenodeonregionface.h"

const float pi = 3.1415926;

StoreDefinitionFileNodeOnRegionFace::StoreDefinitionFileNodeOnRegionFace()
{

}

void StoreDefinitionFileNodeOnRegionFace::storeNodeOnRegionFace(QString mffPath, QList<Face> *regionFace, float disError, float degError)
{
    qDebug()<< endl << "storing...";

    QFile fileIn;
    QTextStream streamIn;
    QString oneLine;
    QStringList sl;

    fileIn.setFileName( mffPath);
    fileIn.open( QFile::ReadOnly|QFile::Text);
    streamIn.setDevice( &fileIn);
    qint64 start;
    start = streamIn.pos();

    while (!streamIn.atEnd() && !oneLine.contains( "MatrixElem"))
        oneLine = streamIn.readLine();
    oneLine = streamIn.readLine();
    sl = oneLine.simplified().split(" ");
    if (oneLine == "")
    {
        qDebug()<<"definition file error, can not find frac nodes number";
        exit(1);//restart file error
    }
    int fracNodeNum = sl[2].toInt() - 1;
    oneLine = "";

    //search nodes on the face
    Node node;
    QVector3D a, b;
    float dis, aDis, bDis, degree = 0;
    streamIn.seek( start);

    //pass header
    while (!oneLine.contains( "NODE"))
        oneLine = streamIn.readLine();

    //pass fracture nodes
    for (int i=0; i<fracNodeNum; i++)
        oneLine = streamIn.readLine();

    //store grid nodes which on the face
    sl[0] = "init";
    while (sl[0] != "0")
    {
        oneLine = streamIn.readLine();
        sl = oneLine.simplified().split(" ");
        node.setNode( sl[1].toFloat(), sl[2].toFloat(), sl[3].toFloat());

        //check whether nodes are in the area
        for (int i=0; i<regionFace->count(); i++)//for each faces
        {
            //check whether nodes are on the plane which contains area
            dis = node.xyz.distanceToPlane( (*regionFace)[i].getApex()[0].xyz, (*regionFace)[i].getApex()[1].xyz, (*regionFace)[i].getApex()[2].xyz);
            if (dis < disError && dis > -disError)
            {
                //only handle convex polygon
                //check whether nodes are in the area or not
                degree = 0;
                int j, k, num = (*regionFace)[i].getApex().count();
                for (j=0, k=num-1; j<num; k=j++)//add degree of all apex
                {
                    a = (*regionFace)[i].getApex()[j].xyz;
                    b = (*regionFace)[i].getApex()[k].xyz;
                    aDis = node.xyz.distanceToPoint( a);
                    bDis = node.xyz.distanceToPoint( b);
                    if (aDis*bDis == 0)//on the apex
                    {
                        degree = 360;
                        j = num;
                    }
                    else
                        degree = degree + (acos( a.dotProduct( a-node.xyz, b-node.xyz) / (aDis * bDis)) * 180 / pi);
                }

                //store nodes in the area
                if ( (degree <= 360+degError && degree >= 360-degError))//in the area -> store
                {
                    (*regionFace)[i].addNodeOnFace( sl[0].toInt(), sl[1].toFloat(), sl[2].toFloat(), sl[3].toFloat(),
                            sl[4].toInt(), sl[5].toDouble(), sl[6].toDouble(), sl[7].toInt());
                }
            }
        }
    }
    fileIn.close();
    qDebug() << "store complete" << endl;
}
