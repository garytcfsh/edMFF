/*
exit code
    1 for input file error
    2 for input argument error
    3 for select stop

*/



#include "edmff.h"

EdMff::EdMff()
{
    regionFace = new QList< Face>;
}

QString EdMff::readRegion()
{
    QFile fileIn;
    QTextStream streamIn;
    QString oneLine;
    QStringList sl;

    qDebug()<< endl << "region file (.sab): ";
    QTextStream path( stdin);
    regionPath = path.readLine();
    fileIn.setFileName( regionPath);
    fileIn.open( QFile::ReadOnly|QFile::Text);
    streamIn.setDevice( &fileIn);

    while (!streamIn.atEnd())
    {
        oneLine = streamIn.readLine();
        if (oneLine.contains( "box_region"))
        {
            fileIn.close();
            return "box";
        }
        else if (oneLine.contains( "slab_region"))
        {
            fileIn.close();
            return "slab";
        }
    }
    fileIn.close();
    return "0";//region file error
}
