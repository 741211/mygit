#include "cfgdatamodel.h"
#include <QDebug>
cfgDataModel::cfgDataModel(QObject *parent) : QObject(parent)
{

}

void cfgDataModel::setData(QList<QString> nrateList, QList<Chart> chartList)
{
    nrateLists=nrateList;
    channelList=chartList;
    emit signalInit(nrateLists,channelList);
}

void cfgDataModel::getCId(const QString &s)
{
    if(channelList.isEmpty()) return;
    int it=0;
    for(int i=0;i<channelList.size();i++){
        if(channelList[i].charName==s) it=i;
    }
    emit signalId(it);
}
void cfgDataModel::getTypeList(const QString &s)
{
    if(channelList.isEmpty()) return;
    QList<QString> typeS;
    int k=0,num=0;
    typeS.clear();
    for(int i=0;i<channelList.size();i++){
        QString str=channelList[i].unit;
        if(str.right(1).toUpper()==s) {
            k++;
            if(k==1) num=i;
            typeS.append(channelList[i].charName);
        }
    }
    k=0;
    emit signalList(typeS);
    emit signalId(num);
}
