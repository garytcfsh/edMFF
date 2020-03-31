#include "node.h"

Node::Node()
{

}

Node::Node(QVector3D vector)
{
    xyz = vector;
}

Node::Node(float x, float y, float z)
{
    xyz.setX(x);
    xyz.setY(y);
    xyz.setZ(z);
}

Node::Node(int n, float x, float y, float z, int t, double h, double f, int g)
{
    num = n;
    xyz.setX(x);
    xyz.setY(y);
    xyz.setZ(z);
    type = t;
    head = h;
    flux = f;
    group = g;
}

void Node::setNode(float x, float y, float z)
{
    xyz.setX(x);
    xyz.setY(y);
    xyz.setZ(z);
}


void Node::setNode(int type, double head, double flux, int group)
{
    this->type = type;
    this->head = head;
    this->flux = flux;
    this->group = group;
}
