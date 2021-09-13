#ifndef STEADYDATAMODEL_H
#define STEADYDATAMODEL_H
#include "fthreadwork.h"

#include <QMetaType>
#include <QObject>
#include <QVector>
struct fftData{
    double amplitude;
    double phase;
    double frequency;
};
struct fftTime{
    double t1;
    double t2;
};
Q_DECLARE_METATYPE(fftData)
Q_DECLARE_METATYPE(fftTime)
class steadyDataModel : public QObject
{
    Q_OBJECT
public:
    QVector<double> x,y;
    QString Yunit;
    QVector<fftData> fData;
    QVector<fftTime> fTime;
    QVector<QVector<double>> trans;
    fThreadWork *fWork;
    explicit steadyDataModel(QObject *parent = 0);
signals:
    void signalFFTStart(QVector<double> v,const double& FS);
    void signalFFTInfo(double maxU, double F, double phase,QVector<double> y);
    void signalChartInfo(QVector<double> xData,QVector<double> yData,const QString& unit);
public slots:
    void setData(QVector<double> xData,QVector<double> yData,const QString& unit);
    void setfftData(double maxU, double F, double phase, QVector<double> y);
    void CalFFT(const double& t1,const double& t2);
};

#endif // STEADYDATAMODEL_H
