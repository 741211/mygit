#ifndef TRANSIENTDATAMODEL_H
#define TRANSIENTDATAMODEL_H

#include <QObject>
#include <QVector>

class transientDataModel : public QObject
{
    Q_OBJECT
public:
    QVector<double> x,y;
    QString Yunit;
    explicit transientDataModel(QObject *parent = 0);

signals:
     void signalChartInfo(QVector<double> xData,QVector<double> yData,const QString& unit);
public slots:
    void setData(QVector<double> xData,QVector<double> yData,const QString& unit);
};

#endif // TRANSIENTDATAMODEL_H
