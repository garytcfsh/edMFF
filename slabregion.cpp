#include "slabregion.h"

const float pi = 3.1415926;

SlabRegion::SlabRegion()
{

}

void SlabRegion::setRegionFace(QString regionPath, QList<Face> *regionFace)
{
    float s_len, t_len, h_len;
    float scan_trend, scan_plunge, tran_trend, tran_plunge, high_trend, high_plunge;
    QVector3D center;

    QFile fileIn;
    QTextStream streamIn;
    QString oneLine;
    QStringList sl;

    fileIn.setFileName( regionPath);
    fileIn.open( QFile::ReadOnly|QFile::Text);
    streamIn.setDevice( &fileIn);

    int check = 0;
    while (!streamIn.atEnd())
    {
        oneLine = streamIn.readLine();
        if (oneLine.contains( "slab_region"))
        {
            check = 1;
            oneLine = streamIn.readLine();
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            center.setX( sl[2].toFloat());
            center.setY( sl[3].toFloat());
            center.setZ( sl[4].toFloat());
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            s_len = sl[2].toFloat()/2;
            t_len = sl[3].toFloat()/2;
            h_len = sl[4].toFloat()/2;
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            scan_trend = sl[2].toFloat();
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            scan_plunge = sl[2].toFloat();
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            tran_trend = sl[2].toFloat();
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            tran_plunge = sl[2].toFloat();
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            high_trend = sl[2].toFloat();
            oneLine = streamIn.readLine();
            sl = oneLine.simplified().split(" ");
            high_plunge = sl[2].toFloat();
            scan_trend = scan_trend/180*pi;
            scan_plunge = scan_plunge/180*pi;
            tran_trend = tran_trend/180*pi;
            tran_plunge = tran_plunge/180*pi;
            high_trend = high_trend/180*pi;
            high_plunge = high_plunge/180*pi;
            QVector3D scan( s_len*cos(scan_plunge)*sin(scan_trend), s_len*cos(scan_plunge)*cos(scan_trend), s_len*sin(scan_plunge));//Y direction
            QVector3D tran( t_len*cos(tran_plunge)*sin(tran_trend), t_len*cos(tran_plunge)*cos(tran_trend), t_len*sin(tran_plunge));//X
            QVector3D high( h_len*cos(high_plunge)*sin(high_trend), h_len*cos(high_plunge)*cos(high_trend), h_len*sin(high_plunge));//Z

            regionFace->append( Face());//top
            (*regionFace)[0].addApex( center+scan+tran+high);
            (*regionFace)[0].addApex( center+scan-tran+high);
            (*regionFace)[0].addApex( center-scan-tran+high);
            (*regionFace)[0].addApex( center-scan+tran+high);
            regionFace->append( Face());//bot
            (*regionFace)[1].addApex( center+scan+tran-high);
            (*regionFace)[1].addApex( center+scan-tran-high);
            (*regionFace)[1].addApex( center-scan-tran-high);
            (*regionFace)[1].addApex( center-scan+tran-high);
            regionFace->append( Face());//left
            (*regionFace)[2].addApex( center-scan-tran+high);
            (*regionFace)[2].addApex( center-scan-tran-high);
            (*regionFace)[2].addApex( center+scan-tran-high);
            (*regionFace)[2].addApex( center+scan-tran+high);
            regionFace->append( Face());//right
            (*regionFace)[3].addApex( center-scan+tran+high);
            (*regionFace)[3].addApex( center-scan+tran-high);
            (*regionFace)[3].addApex( center+scan+tran-high);
            (*regionFace)[3].addApex( center+scan+tran+high);
            regionFace->append( Face());//near
            (*regionFace)[4].addApex( center-scan-tran+high);
            (*regionFace)[4].addApex( center-scan-tran-high);
            (*regionFace)[4].addApex( center-scan+tran-high);
            (*regionFace)[4].addApex( center-scan+tran+high);
            regionFace->append( Face());//far
            (*regionFace)[5].addApex( center+scan-tran+high);
            (*regionFace)[5].addApex( center+scan-tran-high);
            (*regionFace)[5].addApex( center+scan+tran-high);
            (*regionFace)[5].addApex( center+scan+tran+high);

            QString qs;
            std::string s;
            for (int i=0; i<(*regionFace).count(); i++)
            {
                qs = "Face_" + qs.setNum(i);
                qDebug() << qs << endl
                << (*regionFace)[i].getApex()[0].xyz << endl
                << (*regionFace)[i].getApex()[1].xyz << endl
                << (*regionFace)[i].getApex()[2].xyz << endl
                << (*regionFace)[i].getApex()[3].xyz;

            }
        }
    }
    if (check == 0)
    {
        qDebug()<< "region file error";
        exit(1);
    }
    fileIn.close();
}
