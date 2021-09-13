#include "comtradefile.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
ComtradeFile::ComtradeFile(QObject *parent) : QObject(parent)
{
    cfgFile=new Config;
    connect(this,&ComtradeFile::readData,this,&ComtradeFile::getFile);
}

void ComtradeFile::readFile(const QString &aFileName)
{
    QFile   aFile(aFileName);
    if (!aFile.exists()) //文件不存在
        return;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream aStream(&aFile); //用文本流读取文件
    aStream.setAutoDetectUnicode(true); //自动检测Unicode,才能正常显示文档内的汉字
    QString s[1000];
    int k=0;
    while (!aStream.atEnd())
    {
       QString str=aStream.readLine();//读取文件的一行
       s[k]=str;
        k++;
    }
    for(int i=0;i<k;i++){
        QList<QString> str1=s[i].split(",");
        if(i==0){
            cfgFile->station_name=str1[0];
            cfgFile->rec_dev__id=str1[1];
            if(str1.length()==3) cfgFile->rev_year=str1[2].toInt();
        }
        else if(i==1){
            cfgFile->TT=str1[0].toInt();
            cfgFile->Anum=str1[1].left(str1[1].length()-1).toInt();
            cfgFile->Dnum=str1[2].left(str1[2].length()-1).toInt();
        }
        else if(i>1&&i<cfgFile->Anum+2){
            //int y=cfgFile1.Anum;
            cfgFile->as[i-2].an=str1[0].toInt();
            cfgFile->as[i-2].ch_id=str1[1];
            cfgFile->as[i-2].ph=str1[2];
            cfgFile->as[i-2].ccbm=str1[3];
            cfgFile->as[i-2].uu=str1[4];
            cfgFile->as[i-2].a=str1[5].toDouble();
            cfgFile->as[i-2].b=str1[6].toDouble();
            cfgFile->as[i-2].skew=str1[7].toDouble();
            cfgFile->as[i-2].min=str1[8].toInt();
            cfgFile->as[i-2].max=str1[9].toInt();
            if(str1.size()>10){
                cfgFile->as[i-2].primary=str1[10].toDouble();
                cfgFile->as[i-2].secondary=str1[11].toDouble();
                cfgFile->as[i-2].ps=str1[12];
            }
        }
        else if(i>cfgFile->Anum+1&&i<(cfgFile->Anum+cfgFile->Dnum+2)){
            int y=cfgFile->Anum+2;
            cfgFile->ds[i-y].dn=str1[0].toInt();
            cfgFile->ds[i-y].ch_id=str1[1];
            if(str1.size()>10){
                cfgFile->ds[i-y].ph=str1[2];
                cfgFile->ds[i-y].ccbm=str1[3];
                cfgFile->ds[i-y].y=str1[4].toInt();
            }
            else cfgFile->ds[i-y].y=str1[2].toInt();
        }
        else if(i>cfgFile->Anum+cfgFile->Dnum+1&&i<=cfgFile->Anum+cfgFile->Dnum+2){
            cfgFile->IF=str1[0].toDouble();
        }
        else if(i>cfgFile->Anum+cfgFile->Dnum+2&&i<=cfgFile->Anum+cfgFile->Dnum+3){
            cfgFile->nrates=str1[0].toInt();
        }
        else if(i>cfgFile->Anum+cfgFile->Dnum+3&&i<=cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+3&&cfgFile->nrates!=0){
            int x=cfgFile->Anum+cfgFile->Dnum+4;
            cfgFile->nrate[i-x].samp=str1[0].toInt();
            cfgFile->nrate[i-x].endsamp=str1[1].toLongLong();
        }
        else if(i>cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+3&&i<=cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+4){
            cfgFile->firstTime.date1=str1[0];
            cfgFile->firstTime.date2=str1[1];
        }
        else if(i>cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+4&&i<=cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+5){
            cfgFile->secondTime.date1=str1[0];
            cfgFile->secondTime.date2=str1[1];
        }
        else if(i>cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+5&&i<=cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+6){
            cfgFile->ft=str1[0];
        }
        else if(i>cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+6&&i<=cfgFile->Anum+cfgFile->Dnum+cfgFile->nrates+7&&cfgFile->rev_year==1999){
            cfgFile->timemult=str1[0].toDouble();
        }
    }
    aFile.close();
    QString name=aFileName.left(aFileName.length()-3).append("dat");
    fileName=name;
    emit readData(name);
}

void ComtradeFile::getFile(const QString &aFileName)
{
    if(cfgFile->ft.toUpper()=="ASCII") readByAscII(aFileName);
    else readByBinary(aFileName);
}

void ComtradeFile::readByAscII(const QString &aFileName)
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
        dealDataStr(dataStr1);
    }
    else {
        dealDataStr(dataStr);
    }
    aFile.close();
}

void ComtradeFile::readByBinary(const QString &aFileName)
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
    dealDataVector(data);
    data.clear();
    file.close();
}

void ComtradeFile::dealDataStr(QList<QString> dataStr)
{
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
    cfgFile->waveLength=x.last()-x.first();
    dataCharts.clear();
    dataCharts=dataChart;
    dataChart.clear();
    emit signalCFG(cfgFile,fileName);
    getCharts();
}

void ComtradeFile::dealDataVector(QVector<QVector<ushort> > data)
{
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
    cfgFile->waveLength=x.last()-x.first();
    dataCharts.clear();
    dataCharts=dataChart;
    dataChart.clear();
    emit signalCFG(cfgFile,fileName);
    getCharts();
}

void ComtradeFile::getSchart(const int &id)
{
    emit signalSChart(x,dataCharts[id],chartList[id].unit);
}

void ComtradeFile::getTchart(const int &id)
{
    emit signalTChart(x,dataCharts[id],chartList[id].unit);
}

void ComtradeFile::getCharts()
{
    chartList.clear();
    for(int j=0;j<cfgFile->Anum;j++){
        Chart chart;
        if(j<cfgFile->Anum){
            QString s=cfgFile->as[j].ch_id;
            chart.charName=s.append("("+cfgFile->as[j].ph+tr("相)"));
            chart.ph_id=cfgFile->as[j].ch_id;
            chart.ph=cfgFile->as[j].ph;
            chart.unit=cfgFile->as[j].uu;
            auto max = std::max_element(std::begin(dataCharts[j]), std::end(dataCharts[j]));
            auto min = std::min_element(std::begin(dataCharts[j]), std::end(dataCharts[j]));
            double a=*max;
            double b=*min;
            chart.min=b;
            chart.max=a;
        }
        chartList.append(chart);
    }
    QList<QString> nrateList;
    for(int i=0;i<cfgFile->nrates;i++){
        QString str=QString::number(i+1).append(".采样率=%1,采样终点=%2").
                arg(QString::number(cfgFile->nrate[i].samp)).arg(QString::number(cfgFile->nrate[i].endsamp));
        nrateList.append(str);
    }

    emit signalChan(nrateList,chartList);
}
