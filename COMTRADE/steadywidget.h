#ifndef STEADYWIDGET_H
#define STEADYWIDGET_H

#include "wavewidget.h"

#include <QWidget>

namespace Ui {
class SteadyWidget;
}
class WaveWiget;
class SteadyWidget : public QWidget
{
    Q_OBJECT

public:
    WaveWidget *wave;
    explicit SteadyWidget(QWidget *parent = 0);
    ~SteadyWidget();
public slots:
    //void paint(QVector<double> xData, QVector<double> yData, const QString &unit);
    void toFFT(const double& t1,const double& t2);
    void displayFFTInfo(double maxU, double F, double phase,QVector<double> y);
signals:
    void startP(QVector<double> xData, QVector<double> yData, const QString &unit);
    void signalWaveTime(const double& t1,const double& t2);
private:
    Ui::SteadyWidget *ui;
};

#endif // STEADYWIDGET_H
