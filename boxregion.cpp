#include "boxregion.h"

const float pi = 3.1415926;

BoxRegion::BoxRegion()
{

}

void BoxRegion::setRegionFace(QString regionPath, QList< Face> *regionFace)
{
    QFile fileIn;
    QTextStream streamIn;
    QString oneLine;
    QStringList sl;

    fileIn.setFileName( regionPath);
    fileIn.open( QFile::ReadOnly|QFile::Text);
    streamIn.setDevice( &fileIn);

    while (!streamIn.atEnd())
    {
        oneLine = streamIn.readLine();
        float cenx, ceny, cenz, lenx, leny, lenz;
        float *x, *y, *z;

        oneLine = streamIn.readLine();
        oneLine = streamIn.readLine();
        sl = oneLine.simplified().split(" ");
        cenx = sl[2].toFloat();
        ceny = sl[3].toFloat();
        cenz = sl[4].toFloat();
        oneLine = streamIn.readLine();
        sl = oneLine.simplified().split(" ");
        lenx = sl[2].toFloat()/2;
        leny = sl[3].toFloat()/2;
        lenz = sl[4].toFloat()/2;

        x = new float[8];
        y = new float[8];
        z = new float[8];
        x[0] = cenx - lenx;
        y[0] = ceny - leny;
        z[0] = cenz + lenz;
        x[1] = cenx + lenx;
        y[1] = ceny - leny;
        z[1] = cenz + lenz;
        x[2] = cenx + lenx;
        y[2] = ceny + leny;
        z[2] = cenz + lenz;
        x[3] = cenx - lenx;
        y[3] = ceny + leny;
        z[3] = cenz + lenz;
        x[4] = cenx - lenx;
        y[4] = ceny - leny;
        z[4] = cenz - lenz;
        x[5] = cenx + lenx;
        y[5] = ceny - leny;
        z[5] = cenz - lenz;
        x[6] = cenx + lenx;
        y[6] = ceny + leny;
        z[6] = cenz - lenz;
        x[7] = cenx - lenx;
        y[7] = ceny + leny;
        z[7] = cenz - lenz;

        regionFace->append( Face());
        (*regionFace)[0].addApex( x[3], y[3], z[3]);
        (*regionFace)[0].addApex( x[0], y[0], z[0]);
        (*regionFace)[0].addApex( x[1], y[1], z[1]);
        (*regionFace)[0].addApex( x[2], y[2], z[2]);
        regionFace->append( Face());
        (*regionFace)[1].addApex( x[4], y[4], z[4]);
        (*regionFace)[1].addApex( x[5], y[5], z[5]);
        (*regionFace)[1].addApex( x[6], y[6], z[6]);
        (*regionFace)[1].addApex( x[7], y[7], z[7]);
        regionFace->append( Face());
        (*regionFace)[2].addApex( x[0], y[0], z[0]);
        (*regionFace)[2].addApex( x[4], y[4], z[4]);
        (*regionFace)[2].addApex( x[7], y[7], z[7]);
        (*regionFace)[2].addApex( x[3], y[3], z[3]);
        regionFace->append( Face());
        (*regionFace)[3].addApex( x[1], y[1], z[1]);
        (*regionFace)[3].addApex( x[5], y[5], z[5]);
        (*regionFace)[3].addApex( x[6], y[6], z[6]);
        (*regionFace)[3].addApex( x[2], y[2], z[2]);
        regionFace->append( Face());
        (*regionFace)[4].addApex( x[0], y[0], z[0]);
        (*regionFace)[4].addApex( x[4], y[4], z[4]);
        (*regionFace)[4].addApex( x[5], y[5], z[5]);
        (*regionFace)[4].addApex( x[1], y[1], z[1]);
        regionFace->append( Face());
        (*regionFace)[5].addApex( x[3], y[3], z[3]);
        (*regionFace)[5].addApex( x[7], y[7], z[7]);
        (*regionFace)[5].addApex( x[6], y[6], z[6]);
        (*regionFace)[5].addApex( x[2], y[2], z[2]);

    }
    fileIn.close();
}
