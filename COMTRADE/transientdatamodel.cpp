#include "transientdatamodel.h"

transientDataModel::transientDataModel(QObject *parent) : QObject(parent)
{

}

void transientDataModel::setData(QVector<double> xData, QVector<double> yData, const QString &unit)
{
    if(xData.isEmpty()||yData.isEmpty()) return;
    x.clear();
    y.clear();
    x=xData;
    y=yData;
    Yunit=unit;
    emit signalChartInfo(xData,yData,Yunit);
}
