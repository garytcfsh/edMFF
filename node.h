#ifndef NODE_H
#define NODE_H

#include <QVector3D>

class Node
{
public:
    Node();
    Node(QVector3D);
    Node(float, float, float);
    Node(int, float, float, float, int, double, double, int);
    void setNode(float, float, float);
    void setNode(int, double, double, int);

    QVector3D xyz;
    int num, type, group;
    double head, flux;
};

#endif // NODE_H
