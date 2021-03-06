#include "dfn2hybrid.h"

DFN2Hybrid::DFN2Hybrid()
{
//    fracBD = new QList< BoundaryCondition>;
//    hybridBD = new QList< BoundaryCondition>;
}

int DFN2Hybrid::merge(QString dfnPath, QString hybridPath)
{
    qDebug()<< endl << "merging file...";
    QFile fFile, hFile, outFile;
    QTextStream fStream, hStream, outStream;
    QString fOneline, hOneline;
    QStringList fSl, hSl;

    fFile.setFileName( dfnPath);
    fFile.open( QFile::ReadOnly|QFile::Text);
    fStream.setDevice( &fFile);
    hFile.setFileName( hybridPath);
    hFile.open( QFile::ReadOnly|QFile::Text);
    hStream.setDevice( &hFile);
    outFile.setFileName( hybridPath + "merge");
    outFile.open( QFile::WriteOnly|QFile::Text);
    outStream.setDevice( &outFile);


    int dfnFracNodeNum = 0, hybridFracNodeNum = 0;
    qint64 hStart = hStream.pos(), fStart = fStream.pos();

    //judge which one has more frac nodes
    while (!hStream.atEnd() && !hOneline.contains( "MatrixElem"))
        hOneline = hStream.readLine();
    hOneline = hStream.readLine();
    hSl = hOneline.simplified().split(" ");
    if (hOneline == "")
    {
        qDebug()<<"definition file error, can not find frac nodes number";
        exit(1);//restart file error
    }
    hybridFracNodeNum = hSl[2].toInt() - 1;
    hOneline = "";
    hStream.seek(hStart);

    while (!fOneline.contains("NODE"))//skip dfn header
        fOneline = fStream.readLine();
    fOneline = fStream.readLine();
    fSl = fOneline.simplified().split(" ");
    while (fSl[0] != "0")//write dfn frac node to new file
    {
        fOneline = fStream.readLine();
        fSl = fOneline.simplified().split(" ");
        dfnFracNodeNum++;
    }
    fOneline = "";
    fStream.seek(fStart);

    if (dfnFracNodeNum < hybridFracNodeNum)
    {
        int i=0;
        QString name, group, type;
        while (!hOneline.contains("NODE"))//write hybrid header to new file
        {
            hOneline = hStream.readLine();
            outStream << hOneline << endl;

            if (hOneline.contains( "BOUNDARY GROUP"))
            {
                hybridBD.append( BoundaryCondition());
                hSl = hOneline.simplified().split(" ");
                name = hSl[4].remove('"');
                group = hSl[3].remove(":");
                type = hSl[6];
                hybridBD[i].init( name, group, type);
                i++;
            }
        }
        i=0;
        while (!fOneline.contains("NODE"))//skip dfn header
        {
            fOneline = fStream.readLine();

            if (fOneline.contains( "BOUNDARY GROUP"))
            {
                fracBD.append( BoundaryCondition());
                fSl = fOneline.simplified().split(" ");
                name = fSl[4].remove('"');
                group = fSl[3].remove(":");
                type = fSl[6];
                fracBD[i].init( name, group, type);
                i++;
            }
        }

        //error handling
        int bd = 1;
        if (fracBD.count() == hybridBD.count())
        {
            for (int i=0; i<fracBD.count(); i++)
            {
                if (fracBD[i].getName() != hybridBD[i].getName())
                {
                    bd = 0;
                }
            }
        }
        else
        {
            bd = 0;
        }
        if (bd == 0)
        {
            qDebug()<<"";
            qDebug()<<"boundary conditions in dfn and hybrid file are different";
            qDebug()<<"do you want to continue? it may make error! (y or n)";
            QTextStream d( stdin);
            QString in = d.readLine();
            if (in == "N" | in == "n")
            {
                qDebug()<<"Exit";
                exit(3);
            }
            else if (in == "Y" | in == "y")
            {
                qDebug()<<"continue to merge";
            }
            else
            {
                qDebug()<<"Exit";
                exit(2);
            }
        }


        fOneline = fStream.readLine();
        fSl = fOneline.simplified().split(" ");
        while (fSl[0] != "0")//write dfn frac node to new file
        {
            outStream << fOneline << endl;
            fOneline = fStream.readLine();
            fSl = fOneline.simplified().split(" ");
            hStream.readLine();//skip hybrid frac node
            hSl = hOneline.simplified().split(" ");
        }
        while (hSl[0] != "FracElem")//write hybrid remain node to new file
        {
            hOneline = hStream.readLine();
            hSl = hOneline.simplified().split(" ");
            outStream << hOneline << endl;
        }
        fStream.readLine();//skip line of FracElem which has been written by hybrid
        fSl[0] = "";
        hSl[0] = "";
        while (fSl[0] != "0") //write dfn fracelem to new file
        {
            fOneline = fStream.readLine();
            fSl = fOneline.simplified().split(" ");
            outStream << fOneline << endl;
        }
        while (hSl[0] != "0")//skip hybrid fracelem
        {
            hOneline = hStream.readLine();
            hSl = hOneline.simplified().split(" ");
        }
        while ( !hStream.atEnd())
        {
            hOneline = hStream.readLine();
            outStream << hOneline << endl;
        }

    }
    else
    {
        //handing with renumber
        int i=0;
        QString name, group, type;
        while (!hOneline.contains("NODE"))//write hybrid header to new file
        {
            hOneline = hStream.readLine();
            outStream << hOneline << endl;

            if (hOneline.contains( "BOUNDARY GROUP"))
            {
                hybridBD.append( BoundaryCondition());
                hSl = hOneline.simplified().split(" ");
                name = hSl[4].remove('"');
                group = hSl[3].remove(":");
                type = hSl[6];
                hybridBD[i].init( name, group, type);
                i++;
            }
        }
        i=0;
        while (!fOneline.contains("NODE"))//skip dfn header
        {
            fOneline = fStream.readLine();

            if (fOneline.contains( "BOUNDARY GROUP"))
            {
                fracBD.append( BoundaryCondition());
                fSl = fOneline.simplified().split(" ");
                name = fSl[4].remove('"');
                group = fSl[3].remove(":");
                type = fSl[6];
                fracBD[i].init( name, group, type);
                i++;
            }
        }

        //error handling
        int bd = 1;
        if (fracBD.count() == hybridBD.count())
        {
            for (int i=0; i<fracBD.count(); i++)
            {
                if (fracBD[i].getName() != hybridBD[i].getName())
                {
                    bd = 0;
                }
            }
        }
        else
        {
            bd = 0;
        }
        if (bd == 0)
        {
            qDebug()<<"";
            qDebug()<<"boundary conditions in dfn and hybrid file are different";
            qDebug()<<"do you want to continue? it may make error! (y or n)";
            QTextStream d( stdin);
            QString in = d.readLine();
            if (in == "N" | in == "n")
            {
                qDebug()<<"Exit";
                exit(3);
            }
            else if (in == "Y" | in == "y")
            {
                qDebug()<<"continue to merge";
            }
            else
            {
                qDebug()<<"Exit";
                exit(2);
            }
        }

        for (int i=0; i<dfnFracNodeNum; i++)
        {
            fOneline = fStream.readLine();
            outStream << fOneline << endl;


        }
        for (int i=0; i<hybridFracNodeNum; i++)//skip hybrid frac node
        {
            hOneline = hStream.readLine();
            hSl = hOneline.simplified().split(" ");
        }
        int difference = dfnFracNodeNum - hybridFracNodeNum;
        while (hSl[0] != "0")//write hybrid remain node to new file
        {
            hOneline = hStream.readLine();
            hSl = hOneline.simplified().split(" ");
            if (hSl[0] != "0")
            {
                hSl[0].setNum(hSl[0].toInt() + difference);
                hOneline = "";
                for (int j=0; j<hSl.count(); j++)
                    hOneline = hOneline + '\t' +hSl[j];
            }
            outStream << hOneline << endl;
        }
        fStream.readLine();//skip line of FracElem which has been written by hybrid
        fSl[0] = "";
        hSl[0] = "";
        while (fSl[0] != "0") //write dfn fracelem to new file
        {
            fOneline = fStream.readLine();
            fSl = fOneline.simplified().split(" ");
            outStream << fOneline << endl;
        }
        while (hSl[0] != "0")//skip hybrid fracelem
        {
            hOneline = hStream.readLine();
            hSl = hOneline.simplified().split(" ");
        }
        hOneline = hStream.readLine();//write text
        outStream << hOneline << endl;
        while ( !hStream.atEnd())//write grid elem
        {
            hOneline = hStream.readLine();
            hSl = hOneline.simplified().split(" ");
            if (hSl[0] != "0")
            {
                for (int k=2; k<10; k++)
                {
                    hSl[k].setNum(hSl[k].toInt() + difference);
                }
                hOneline = "";
                for (int j=0; j<hSl.count(); j++)
                    hOneline = hOneline + '\t' +hSl[j];
            }
            outStream << hOneline << endl;
        }

    }

    fFile.close();
    hFile.close();
    outFile.close();

    qDebug()<< "merged" << endl;
    return dfnFracNodeNum;
}
