#include "dfn2hybrid.h"

DFN2Hybrid::DFN2Hybrid()
{

}

void DFN2Hybrid::merge(QString dfnPath, QString hybridPath)
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

    while (!hOneline.contains("NODE"))//write hybrid header to new file
    {
        hOneline = hStream.readLine();
        outStream << hOneline << endl;
    }
    while (!fOneline.contains("NODE"))//skip dfn header
    {
        fOneline = fStream.readLine();
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

    qDebug()<< "merged" << endl;

}
