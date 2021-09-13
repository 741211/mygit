#include "wavewidget.h"
#include "ui_wavewidget.h"

WaveWidget::WaveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaveWiget)
{
    ui->setupUi(this);
    pixel1=0;
    connect(ui->uPwt,&XcustomPlot::signalPoint,this,[=](int LineType,double x){
        double value=ui->uPwt->graph(0)->data()->findBegin(x)->mainValue();
        if(LineType==1){
            ui->doubleSpinBox->setValue(x);
            ui->labelU4->setStyleSheet("color:red;");
        }
        else {
            ui->doubleSpinBox_2->setValue(x);
            ui->labelU4->setStyleSheet("color:blue;");
            }
        ui->insValue->setText(QString::number(value,'f',2).append(Yunit));
    });
    ui->doubleSpinBox->setKeyboardTracking(false);
    ui->doubleSpinBox_2->setKeyboardTracking(false);
}

WaveWidget::~WaveWidget()
{
    delete ui;
}

void WaveWidget::init(QVector<double> xData, QVector<double> yData, const QString &Yunit)
{
    ui->uPwt->addGraph();
    ui->uPwt->graph(0)->data().data()->clear();
    ui->uPwt->graph(0)->setData(xData,yData);
    Ymax=yData.last();
    Ymin=yData.first();
    width=yData.last()-yData.first();
    Xmax=xData.last();
    Xmin=xData.first();
    lengthMin=xData[5]-xData[0];
    length=xData.last()-xData.first();
    double num=xData[xData.size()-1]/4;
    //ui->uPwt->blueTracer->position->setCoords(num,ui->uPwt->graph(0)->data()->findBegin(num)->mainValue());
    ui->uPwt->xAxis->setLabel("单位：ms");
    ui->uPwt->yAxis->setLabel("单位："+Yunit);
    ui->uPwt->graph(0)->rescaleAxes();
    ui->uPwt->replot();
    getPixel1();
    ui->uPwt->redTracer->position->setCoords(xData[0]+pixel1,yData[0]);
    ui->doubleSpinBox->setValue(xData[0]);
    ui->doubleSpinBox_2->setValue(num);
}

void WaveWidget::getTime()
{
    double t1=ui->uPwt->redTracer->position->key();
    double t2=ui->uPwt->blueTracer->position->key(); 
    if(qAbs(t2-t1)<lengthMin) return;
    emit signalT(t1,t2);
}

void WaveWidget::setTime(const double &t1, const double &t2)
{
    ui->doubleSpinBox->setValue(t1);
    ui->doubleSpinBox_2->setValue(t2);
}
void WaveWidget::getPixel1()
{
    double x1=ui->uPwt->xAxis->range().lower;
    double x2=ui->uPwt->xAxis->range().upper;
    pixel1=(x2-x1)*0.0025;
}

void WaveWidget::on_expansion_clicked()
{
    if(ui->uPwt->graphCount()<1) return;
    double rp=ui->doubleSpinBox->value();
    double bp=ui->doubleSpinBox_2->value();
    if(qAbs(rp-bp)<lengthMin*2) return;
    if(rp>bp) ui->uPwt->xAxis->setRange(bp,rp);
    else ui->uPwt->xAxis->setRange(rp,bp);
    ui->uPwt->replot();
    double rValue=ui->uPwt->graph(0)->data()->findBegin(rp)->mainValue();
    double bValue=ui->uPwt->graph(0)->data()->findBegin(bp)->mainValue();
    getPixel1();
    if(rp>bp){
        ui->uPwt->redTracer->position->setCoords(rp-pixel1,rValue);
        ui->uPwt->blueTracer->position->setCoords(bp+pixel1,bValue);
    }
    else{
        ui->uPwt->redTracer->position->setCoords(rp+pixel1,rValue);
        ui->uPwt->blueTracer->position->setCoords(bp-pixel1,bValue);
    }
    ui->uPwt->replot();
}

void WaveWidget::on_reduction_clicked()
{
    if(ui->uPwt->graphCount()<1) return;
    ui->uPwt->graph(0)->rescaleAxes();
    ui->uPwt->replot();
}
void WaveWidget::on_xE_clicked()
{
    if(ui->uPwt->graphCount()<1) return;
    double min=ui->uPwt->xAxis->range().lower;
    double max=ui->uPwt->xAxis->range().upper;
    max=(min+max)/2;
    if(max-min<length/10)  return;
    ui->uPwt->xAxis->setRange(min,max);
    ui->uPwt->replot();
}

void WaveWidget::on_xR_clicked()
{
    if(ui->uPwt->graphCount()<1) return;
    double min=ui->uPwt->xAxis->range().lower;
    double max=ui->uPwt->xAxis->range().upper;
    max=2*max-min;
    if(max>=Xmax) max=Xmax;
    ui->uPwt->xAxis->setRange(min,max);
    ui->uPwt->replot();
}

void WaveWidget::on_LMove_clicked()
{

    if(ui->uPwt->graphCount()<1) return;
    double min=ui->uPwt->xAxis->range().lower;
    double max=ui->uPwt->xAxis->range().upper;
    double length=(max-min)/5;
    if(min-length<=Xmin){
        min=Xmin;
        max=max-min+Xmin;
    }
    else {
        min=min-length;
        max=max-length;
    }
    ui->uPwt->xAxis->setRange(min,max);
    ui->uPwt->replot();
}

void WaveWidget::on_RMove_clicked()
{

    if(ui->uPwt->graphCount()<1) return;
    double min=ui->uPwt->xAxis->range().lower;
    double max=ui->uPwt->xAxis->range().upper;
    double length=(max-min)/5;
    if(max+length>=Xmax){
        min=min+Xmax-max;
        max=Xmax;
    }
    else {
        min=min+length;
        max=max+length;
    }
    ui->uPwt->xAxis->setRange(min,max);
    ui->uPwt->replot();
}


void WaveWidget::on_doubleSpinBox_valueChanged(double arg1)
{
    if(ui->uPwt->graphCount()<1) return;
    double pre=ui->uPwt->redTracer->position->key();
    if(arg1<Xmin||arg1>Xmax){
        ui->doubleSpinBox->setValue(pre);
        return;
    }

    double value=ui->uPwt->graph(0)->data()->findBegin(arg1)->mainValue();
    double realX=0;
    double lower=ui->uPwt->xAxis->range().lower;
    double upper=ui->uPwt->xAxis->range().upper;
    if(arg1-pixel1<lower) realX=lower+pixel1;
    else if(arg1>upper-pixel1) realX=upper-pixel1;
    else realX=arg1;
    ui->uPwt->redTracer->position->setCoords(realX,value);
    ui->labelU4->setStyleSheet("color:red;");
    ui->insValue->setText(QString::number(value,'f',2).append(Yunit));
    ui->uPwt->replot();
    getTime();
}

void WaveWidget::on_doubleSpinBox_2_valueChanged(double arg1)
{
    if(ui->uPwt->graphCount()<1) return;
    double pre=ui->uPwt->blueTracer->position->key();
    if(arg1<Xmin||arg1>Xmax){
        ui->doubleSpinBox_2->setValue(pre);
        return;
    }
    double value=ui->uPwt->graph(0)->data()->findBegin(arg1)->mainValue();
    double realX=0;
    double lower=ui->uPwt->xAxis->range().lower;
    double upper=ui->uPwt->xAxis->range().upper;
    if(arg1-pixel1<lower) realX=lower+pixel1;
    else if(arg1>upper-pixel1) realX=upper-pixel1;
    else realX=arg1;
    ui->uPwt->blueTracer->position->setCoords(realX,value);
    ui->labelU4->setStyleSheet("color:blue;");
    ui->insValue->setText(QString::number(value,'f',2).append(Yunit));
    ui->uPwt->replot();
    getTime();
}
void WaveWidget::on_yE_clicked()
{
    if(ui->uPwt->graphCount()<1) return;
    double min=ui->uPwt->yAxis->range().lower;
    double max=ui->uPwt->yAxis->range().upper;
    double mid=(max-min)/4;
    max=max-mid;
    min=min+mid;
    ui->uPwt->yAxis->setRange(min,max);
    ui->uPwt->replot();
}

void WaveWidget::on_yR_clicked()
{
    if(ui->uPwt->graphCount()<1) return;
    double min=ui->uPwt->yAxis->range().lower;
    double max=ui->uPwt->yAxis->range().upper;
    double mid=(max-min)/4;
    max=mid+max;
    min=min-mid;
    ui->uPwt->yAxis->setRange(min,max);
    ui->uPwt->replot();
}
