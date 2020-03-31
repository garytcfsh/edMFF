#ifndef FACE_H
#define FACE_H

#include <QVector3D>
#include <QList>
#include <node.h>

class Face
{
public:
    Face();

    void addApex(float, float, float);
    void addApex(QVector3D);
    void addNodeOnFace(int, float, float, float, int, double, double, int);
    double findNearestHead(Node);
    int findNearestNode(Node);
    QList< Node> getApex();
    QList< Node> getNodeOnFace();


private:
    QList< Node> apex, nodeOnFace;

};

#endif // FACE_H
