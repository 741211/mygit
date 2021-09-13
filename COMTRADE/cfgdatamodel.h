#ifndef CFGDATAMODEL_H
#define CFGDATAMODEL_H

#include "comtradefile.h"

#include <QObject>
struct Chart;
class cfgDataModel : public QObject
{
    Q_OBJECT
public:
    QList<Chart>  channelList;
    QList<QString> nrateLists;
    explicit cfgDataModel(QObject *parent = 0);
signals:
    void signalInit(QList<QString> nrateList,QList<Chart>  chartList);
    void signalList(QList<QString> list);
    void signalId(const int& id);
public slots:
    void setData(QList<QString> nrateList,QList<Chart>  chartList);
    void getCId(const QString& s);
    void getTypeList(const QString& s);
};

#endif // CFGDATAMODEL_H
