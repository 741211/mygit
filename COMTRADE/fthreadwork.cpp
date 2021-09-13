#include "fthreadwork.h"
#include<QtMath>
#include<QDebug>
#define N 40000

fThreadWork::fThreadWork(QObject *parent) : QObject(parent)
{

}

void fThreadWork::FFT(QVector<double> v, double FS)
{
    in1_c = (double*)fftw_malloc(sizeof(double)* N);//申请动态内存,这里构造二维数组的方式值得学习
    for(auto i=0;i<N;i++){
        if(i<v.size()) in1_c[i]=v[i];
        else in1_c[i]=0;
    }
    out1_c = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)* N);
    fftw_plan p = FFTW3_H::fftw_plan_dft_r2c_1d(N, in1_c, out1_c, FFTW_ESTIMATE);
    fftw_execute(p);//执行变换

    QVector<double> y;
    y.clear();
    auto SN=v.size();
    for (auto n = 0; n<N/2; n++)
    {
        double u=out1_c[n][0]*out1_c[n][0]+out1_c[n][1]*out1_c[n][1];
        double u2=sqrt(u)*2/SN;
        y.append(u2/sqrt(2));
    }
    auto max = std::max_element(std::begin(y), std::end(y));
    double biggest = *max;
    auto positionmax = std::distance(std::begin(y),max);
    double F=(double)positionmax/N*FS;
    double phase=atan2(out1_c[positionmax][1],out1_c[positionmax][0])*180/M_PI;
    fftw_destroy_plan(p);//销毁策略
    fftw_free(in1_c);
    fftw_free(out1_c);//释放内存
    emit signalFFT(biggest,F,phase,y);
}
