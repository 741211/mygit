#include "steadydatamodel.h"
#include <QDebug>
steadyDataModel::steadyDataModel(QObject *parent) : QObject(parent)
{
    fWork=new fThreadWork;
    connect(this,&steadyDataModel::signalFFTStart,fWork,&fThreadWork::FFT);
    connect(fWork,&fThreadWork::signalFFT,this,&steadyDataModel::setfftData);
}

void steadyDataModel::setData(QVector<double> xData, QVector<double> yData, const QString &unit)
{
    if(xData.isEmpty()||yData.isEmpty()) return;
    x.clear();
    y.clear();
    x=xData;
    y=yData;
    Yunit=unit;
    fTime.clear();
    fData.clear();
    trans.clear();
    emit signalChartInfo(xData,yData,Yunit);
}

void steadyDataModel::setfftData(double maxU, double F, double phase,QVector<double> y)
{
    fftData f;
    f.amplitude=maxU;
    f.phase=phase;
    f.frequency=F;
    fData.append(f);
    trans.append(y);
    emit signalFFTInfo(maxU,F,phase,y);
}

void steadyDataModel::CalFFT(const double &t1, const double &t2)
{
    QVector<fftTime>::iterator ite=std::find_if(fTime.begin(),fTime.end(),[t1,t2](fftTime t){
         return (t.t1==t1&&t.t2==t2);
    });
    auto p=ite-fTime.begin();
    if(ite!=fTime.end()){
        emit signalFFTInfo(fData[p].amplitude,fData[p].frequency,fData[p].phase,trans[p]);
        return;
    }
    QVector<double> v;
    QVector<double>::iterator it=std::find_if(x.begin(),x.end(),[t1](double num){
        return num>=t1;
    });
    auto w=it-x.begin();
    QVector<double>::iterator it_1=std::find_if(x.begin(),x.end(),[t2](double num){
        return num>=t2;
    });
    auto w_1=it_1-x.begin();
    if(w_1-w<2) return;
    double FS=1000/(x[w+1]-x[w]);
    for(auto i=w;i<w_1;i++){
        v.append(y[i]);
    }
    fftTime t;
    t.t1=t1;
    t.t2=t2;
    fTime.append(t);
    emit signalFFTStart(v,FS);
    v.clear();
}
