#include "readdatafile.h"

#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>
#include <QDataStream>
#include <QDebug>
#include <algorithm>

ReadDataFile::ReadDataFile(QObject *parent) : QObject(parent)
{

}
void ReadDataFile::getFile(const QString &aFileName, const Config *cfgFile, const int numcfg)
{
    if(cfgFile->ft.toUpper()=="ASCII") readByAscII(aFileName, cfgFile, numcfg);
    else readByBinary(aFileName, cfgFile, numcfg);
}
void ReadDataFile::readByAscII(const QString &aFileName, const Config *cfgFile, const int numcfg)
{
    QFile   aFile(aFileName);
    if (!aFile.exists()) //文件不存在
        return;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream aStream(&aFile); //用文本流读取文件
    QList<QString> dataStr;
    QList<QString> dataStr1;
    dataStr.clear();
    dataStr1.clear();
    int k=0;
    while (!aStream.atEnd())
    {
       QString str=aStream.readLine();//读取文件的一行
       dataStr.append(str);
       k++;
    }
    if(k>20000){
        int time=k/10000;
        for(int i=0;i<dataStr.size();i++){
            if(i%time==0) dataStr1.append(dataStr[i]);
        }
        auto num=dataStr.size()-1;
        if(num%time!=0) dataStr1.append(dataStr[num]);
        dealDataStr(cfgFile,dataStr1,numcfg);
    }
    else {
        dealDataStr(cfgFile,dataStr,numcfg);
    }
    aFile.close();
}

void ReadDataFile::readByBinary(const QString &aFileName, const Config *cfgFile, const int numcfg)
{

    QFile file(aFileName);
    file.open(QIODevice::ReadOnly);
    int num=cfgFile->Anum+4+cfgFile->Dnum/16;
    if(cfgFile->Dnum%16!=0) num++;
    ushort a[num];
    QVector<ushort> b;
    b.reserve(num);
    QVector<QVector<ushort>> data;
    auto sizeF=file.size()/(num*2);
    int k=1;
    if(sizeF>20000){
        k=sizeF/10000;
    }
    auto cnt=0;
    while(file.read((char *)&a, sizeof(a))){
        if(cnt%k==0)
        {
            for(int i=0;i<num;i++)
                b.append(a[i]);
            data.append(b);
            b.clear();
        }
        cnt++;
    }
    if(sizeF%k!=0){
        for(int i=0;i<num;i++){
            b.append(a[i]);
        }
        data.append(b);
        b.clear();
    }
    dealDataVector(cfgFile,data,numcfg);
    data.clear();

    file.close();
}

void ReadDataFile::dealDataStr(const Config *cfgFile, QList<QString> dataStr, const int numcfg)
{
    QVector<double> x;
    x.clear();
    QVector<QVector<double>> dataChart(cfgFile->Anum+cfgFile->Dnum);
    for(int i=0;i<dataStr.size();i++){
        QList<QString> str1=dataStr[i].split(",");
        for(int j=1;j<cfgFile->Anum+cfgFile->Dnum+2;j++){
            if(j==1){
                x.append(str1[1].toDouble()/1000);
            }
            else if(j>1&&j<cfgFile->Anum+2){
                double a=cfgFile->as[j-2].a;
                double b=cfgFile->as[j-2].b;
                dataChart[j-2].append(str1[j].toDouble()*a+b);
            }
            else{
                dataChart[j-2].append(str1[j].toDouble());
            }
    }
    }
    emit readDataSuccess(cfgFile,dataChart,numcfg,x);
    dataChart.clear();
}

void ReadDataFile::dealDataVector(const Config *cfgFile, QVector<QVector<ushort>> data, const int numcfg)
{
    QVector<double> x;
    x.clear();
    int num=cfgFile->Anum+4+cfgFile->Dnum/16;
    if(cfgFile->Dnum%16!=0) num++;
    QVector<QVector<double>> dataChart(cfgFile->Anum+cfgFile->Dnum);

    for(int i=0;i<data.size();i++){
        QString s;
        for(int j=3;j<num;j++){
            if(j==3){
                double time=(data[i][j]*65536+data[i][j-1])/1000;
                x.append(time);
            }
            else if(j>3&&j<=3+cfgFile->Anum){
                double h=data[i][j];
                double a=cfgFile->as[j-4].a;
                double b=cfgFile->as[j-4].b;
                if(h>32767) h=h-65536;
                h=h*a+b;
                dataChart[j-4].append(h);
            }
            else if(j>=4+cfgFile->Anum){
                int c=j-4-cfgFile->Anum;
                if(c==0){
                    int numD=cfgFile->Dnum%16;
                    if(numD==0) numD=16;
                    s=QString("%1").arg(QString::number(data[i][j]).toInt(), numD, 2, QLatin1Char('0'));
                }
                else{
                    QString str=QString("%1").arg(QString::number(data[i][j]).toInt(), 16, 2, QLatin1Char('0'));
                    s=str.append(s);
                }
            }
        }
        int sH=s.length();
        for(int k=cfgFile->Anum;k<cfgFile->Anum+cfgFile->Dnum;k++){
            QString status=QString(s[sH-1-cfgFile->Anum]);
            dataChart[k].append(status.toDouble());
        }
    }
    emit readDataSuccess(cfgFile,dataChart,numcfg,x);
    dataChart.clear();
}
