#include <QCoreApplication>
#include <iostream>
#include "fixhybriddefinition.h"
#include "setconstanthead.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "Note : " << endl;
    cout << endl << endl << endl;

    std::string line;
    std::cout << "Select a funciton:  1. Fix EPM/DFN  2. Set fracture flow boundary condition" << std::endl;
    std::getline( std::cin, line);
    QString i = "0";
    i = QString( QString::fromLocal8Bit( line.c_str()));
    if (i == "1")
    {
        FixHybridDefinition fixHybridDefinition;
    }
    else if (i == "2")
    {
        SetConstantHead setConstantHead;
    }
    else
    {
        cout << "function error" << endl;
        exit(2);
    }

    return a.exec();
}
