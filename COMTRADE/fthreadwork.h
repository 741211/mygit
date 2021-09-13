#ifndef FTHREADWORK_H
#define FTHREADWORK_H
#include<fftw3.h>
#include <QObject>
#include <QVector>

class fThreadWork : public QObject
{
    Q_OBJECT
public:
    double *in1_c;
    fftw_complex *out1_c;
    explicit fThreadWork(QObject *parent = 0);

signals:
    void signalFFT(double maxU,double F,double phase,QVector<double> y);
public slots:
    void FFT(QVector<double> v,double FS);
};

#endif // FTHREADWORK_H
