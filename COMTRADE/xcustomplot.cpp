#include "xcustomplot.h"

XcustomPlot::XcustomPlot(QWidget *parent):
    QCustomPlot(parent)
{
    cntEvent=0;
    press=false;
    changed=false;
    LineType=redLine;
    redTracer=new QCPItemTracer(this);
    redTracer->setPen(QPen(Qt::red));
    redTracer->setStyle(QCPItemTracer::tsCrosshair);

    blueTracer=new QCPItemTracer(this);
    blueTracer->setPen(QPen(Qt::blue));
    blueTracer->setStyle(QCPItemTracer::tsCrosshair);
    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}
void XcustomPlot::mouseMoveEvent(QMouseEvent *e)
{
    if(!this->graphCount()){
        return;
    }
    double mousepos=this->xAxis->pixelToCoord(e->pos().x());

    double mousepos1=this->yAxis->pixelToCoord(e->pos().y());
    double mouseposRed=redTracer->position->key();
    double mouseposBlue=blueTracer->position->key();
    double precision=(this->xAxis->tickVectorLabels()[1].toDouble()-this->xAxis->tickVectorLabels()[0].toDouble())/100;
    if(mouseposRed!=mouseposBlue){
        if(mouseposRed>=mousepos-precision&&mouseposRed<=mousepos+precision&&mousepos1>this->yAxis->range().lower&&
                mousepos1<this->yAxis->range().upper){
            if(press==false){
                this->setCursor(Qt::SizeHorCursor);
                changed=true;
                LineType=redLine;
            }
        }
        else if(mouseposBlue>=mousepos-precision&&mouseposBlue<=mousepos+precision&&mousepos1>this->yAxis->range().lower&&
                mousepos1<this->yAxis->range().upper){
            if(press==false){
                this->setCursor(Qt::SizeHorCursor);
                changed=true;
                LineType=blueLine;
            }
        }
        else{

            if(press==false||changed==false){
                changed=false;
                this->setCursor(Qt::ArrowCursor);
            }
        }
    }
    else{
        if(LineType==blueLine){
            if(mouseposBlue>=mousepos-precision&&mouseposBlue<=mousepos+precision&&mousepos1>this->yAxis->range().lower
                    &&mousepos1<this->yAxis->range().upper){
                if(press==false){
                    this->setCursor(Qt::SizeHorCursor);
                    changed=true;
                    LineType=blueLine;
                }
            }
            else{
                if(press==false||changed==false){
                    changed=false;
                    this->setCursor(Qt::ArrowCursor);
                }
            }
        }
        else if(LineType==redLine){
            if(mouseposRed>=mousepos-precision&&mouseposRed<=mousepos+precision&&mousepos1>this->yAxis->range().lower
                    &&mousepos1<this->yAxis->range().upper){
                if(press==false){
                    this->setCursor(Qt::SizeHorCursor);
                    changed=true;
                    LineType=redLine;
                }
            }
            else{
                if(press==false||changed==false){
                    changed=false;
                    this->setCursor(Qt::ArrowCursor);
                }
            }
        }

    }
    if(mousepos1<this->yAxis->range().lower||mousepos1>this->yAxis->range().upper){
        changed=false;
    }
    if(mousepos<this->xAxis->range().lower||mousepos>this->xAxis->range().upper){
        changed=false;
    }
    if(changed==true&&press==true){
        double x = this->xAxis->pixelToCoord(e->pos().x());
        if(x>=this->xAxis->range().lower&&x<=this->xAxis->range().upper){
            if(LineType==redLine) {

                emit signalPoint(redLine,x);
            }
            else
            {
                emit signalPoint(blueLine,x);
            }
        }
    }

}

void XcustomPlot::mousePressEvent(QMouseEvent *e)
{
    double mousepos=this->xAxis->pixelToCoord(e->pos().x());
    double mousepos1=this->yAxis->pixelToCoord(e->pos().y());
    if(e->button()==Qt::LeftButton)
   {
        if(mousepos1<=this->yAxis->range().upper&&mousepos1>=this->yAxis->range().lower
                &&this->cursor().shape()==Qt::CursorShape(Qt::SizeHorCursor)){
            if(mousepos<this->xAxis->range().lower) mousepos=this->xAxis->range().lower;
            if(mousepos>this->xAxis->range().upper) mousepos=this->xAxis->range().upper;
            emit signalPoint(LineType,mousepos);
        }
        press=true;
   }

}

void XcustomPlot::mouseReleaseEvent(QMouseEvent *e)
{
    press=false;
}

void XcustomPlot::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(!this->graphCount()){
        return;
    }
    double mkey=this->redTracer->position->key()-this->blueTracer->position->key();
    double mousepos=this->xAxis->pixelToCoord(e->pos().x());
    double mousepos1=this->yAxis->pixelToCoord(e->pos().y());
    if(mousepos<this->xAxis->range().lower||mousepos>this->xAxis->range().upper||
            mousepos1<this->yAxis->range().lower||mousepos1>this->yAxis->range().upper) return;
    double key=0;
    if(mkey>0){
        if(mkey<=mousepos-this->xAxis->range().lower){
            key=mousepos-mkey;
        }
        else {
           key=this->xAxis->range().lower;
        }
    }
    else {
        if(-mkey<=this->xAxis->range().upper-mousepos){
            key=mousepos-mkey;
        }
        else {
            key=this->xAxis->range().upper;
        }
    }
    emit signalPoint(blueLine,key);
    emit signalPoint(redLine,mousepos);
}
