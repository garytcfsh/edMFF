#include "face.h"
#include <QDebug>

Face::Face()
{


}

void Face::addApex(float x, float y, float z)
{
    apex.append( Node( x, y, z));
}

void Face::addApex(QVector3D vector)
{
    apex.append( Node( vector));
}

void Face::addNodeOnFace(int n, float x, float y, float z, int t, double h, double f, int g)
{
    nodeOnFace.append( Node(n, x, y, z, t, h, h, g));
}

double Face::findNearestHead(Node node)
{
    float dis = 0, min;
    double head = 0;

    min = node.xyz.distanceToPoint( nodeOnFace[0].xyz);
    for (int i=0; i<nodeOnFace.count(); i++)
    {
        dis = node.xyz.distanceToPoint( nodeOnFace[i].xyz);
        if (min >= dis)
        {
            min = dis;
            head = nodeOnFace[i].head;
        }
    }

    return head;
}

int Face::findNearestNode(Node node)
{
    float dis = 0, min;
    int nodeNum;

    min = node.xyz.distanceToPoint( nodeOnFace[0].xyz);
    for (int i=0; i<nodeOnFace.count(); i++)
    {
        dis = node.xyz.distanceToPoint( nodeOnFace[i].xyz);
        if (min >= dis)
        {
            min = dis;
            nodeNum = nodeOnFace[i].num;
        }
    }

    return nodeNum;
}

QList< Node> Face::getApex()
{
    return apex;
}

QList< Node> Face::getNodeOnFace()
{
    return nodeOnFace;
}
