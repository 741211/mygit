#ifndef COMTRADEFILE_H
#define COMTRADEFILE_H

#include "config.h"
#include<QMetaType>
#include <QObject>
#include <QVector>

struct Chart{
    QString charName;
    QString ph_id;
    QString ph;
    QString unit;
    double min;
    double max;
};
Q_DECLARE_METATYPE(Chart)
class ComtradeFile : public QObject
{
    Q_OBJECT
public:
    Config *cfgFile;
    QVector<double> x;
    QVector<QVector<double>> dataCharts;
    QList<Chart>  chartList;
    QString fileName;
    explicit ComtradeFile(QObject *parent = 0);
signals:
    void readData(const QString& aFileName);
    void signalCFG(const Config *cfgFile,const QString &aFileName);
    void signalChan(QList<QString> nrateList,QList<Chart>  chartList);
    void signalSChart(QVector<double> x,QVector<double> y,const QString& unit);
    void signalTChart(QVector<double> x,QVector<double> y,const QString& unit);
public slots:
    void readFile(const QString& aFileName);
    void getFile(const QString &aFileName);
    void readByAscII(const QString &aFileName);
    void readByBinary(const QString &aFileName);
    void dealDataStr(QList<QString> dataStr);
    void dealDataVector(QVector<QVector<ushort>> data);
    void getSchart(const int& id);
    void getTchart(const int& id);
    void getCharts();
};

#endif // COMTRADEFILE_H
