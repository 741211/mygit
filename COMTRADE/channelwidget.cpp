#include "channelwidget.h"
#include<QDebug>
#include "ui_channelwidget.h"

ChannelWidget::ChannelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelWidget)
{
    ui->setupUi(this);
    checked=true;
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableWidget->verticalHeader()->setVisible(true);
    connect(ui->rBtnU,&QRadioButton::clicked,this,&ChannelWidget::setChannel);
    connect(ui->rBtnI,&QRadioButton::clicked,this,&ChannelWidget::setChannel);
    connect(ui->comboBox_2,SIGNAL(activated(QString)),this,SLOT(getWaveName(QString)));
}

ChannelWidget::~ChannelWidget()
{
    delete ui;
}

void ChannelWidget::displayChannel(QList<QString> nrateList, QList<Chart> chartList)
{
    if(chartList.isEmpty()||nrateList.isEmpty()) return;
    channelList.clear();
    channelList=chartList;
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox->addItems(nrateList);
    for(int i=0;i<chartList.size();i++){
        QString s=chartList[i].unit;
        if(s.right(1).toUpper()=="V"&&ui->rBtnU->isChecked()){
            ui->comboBox_2->addItem(chartList[i].charName);

        }
        else if(s.right(1).toUpper()=="A"&&ui->rBtnI->isChecked()) {
            ui->comboBox_2->addItem(chartList[i].charName);

        }
    }
    QString s=ui->comboBox_2->itemText(0);
    emit signalWname(s);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    for(int j=0;j<chartList.size();j++){
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(chartList[j].ph_id));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(chartList[j].ph));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(chartList[j].unit));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(chartList[j].max)));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(chartList[j].min)));
    }
}

void ChannelWidget::setChannel()
{
    if(ui->rBtnU->isChecked()==checked||ui->rBtnI->isChecked()!=checked) return;
    ui->comboBox_2->clear();
    if(ui->rBtnU->isChecked()){
        QString s="V";
        emit signalType(s);
        checked=true;
    }
    else if(ui->rBtnI->isChecked()){
        QString s="A";
        emit signalType(s);
        checked=false;
    }
}

void ChannelWidget::getChannel(QList<QString> list)
{
    ui->comboBox_2->addItems(list);
}

void ChannelWidget::getWaveName(const QString &s)
{
    emit signalWname(s);
}
