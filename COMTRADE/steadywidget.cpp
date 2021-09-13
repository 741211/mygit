#include "steadywidget.h"
#include "ui_steadywidget.h"

SteadyWidget::SteadyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SteadyWidget)
{
    ui->setupUi(this);
    wave=new WaveWidget(ui->groupBox);
    connect(this,&SteadyWidget::startP,wave,&WaveWidget::init);
    connect(wave,&WaveWidget::signalT,this,&SteadyWidget::toFFT);
}

SteadyWidget::~SteadyWidget()
{
    delete ui;
}

void SteadyWidget::toFFT(const double &t1, const double &t2)
{
    double x1=t1,x2=t2;
    if(x1>x2) qSwap(x1,x2);
    emit signalWaveTime(x1,x2);
}
void SteadyWidget::displayFFTInfo(double maxU, double F, double phase, QVector<double> y)
{
    ui->amplitude->setText(QString::number(maxU,'f',3));
    ui->frequency->setText(QString::number(F,'f',3));
    ui->phase->setText(QString::number(phase,'f',3));
    QVector<double> x;
    for(int i=0;i<y.size();i++){
        x.append(i);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->data().data()->clear();
    ui->widget->graph(0)->setData(x,y);
    ui->widget->graph(0)->rescaleAxes();
    ui->widget->replot();
}
