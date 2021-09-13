#ifndef READDATAFILE_H
#define READDATAFILE_H

#include "config.h"
#include<QObject>
#include <QList>

class ReadDataFile : public QObject
{
    Q_OBJECT
public:
    explicit ReadDataFile(QObject *parent = 0);
    void readByAscII(const QString &aFileName,const Config *cfgFile,const int numcfg);
    void readByBinary(const QString &aFileName,const Config *cfgFile,const int numcfg);
    void dealDataStr(const Config *cfgFile, QList<QString> dataStr, const int numcfg);
    void dealDataVector(const Config *cfgFile, QVector<QVector<ushort>> data, const int numcfg);
public slots:
    void getFile(const QString &aFileName,const Config *cfgFile,const int numcfg);
signals:
    void readDataSuccess(const Config *cfgFile, QVector<QVector<double>> dataStr,
                         const int numcfg,QVector<double> x);
};

#endif // READDATAFILE_H
