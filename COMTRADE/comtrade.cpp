#include "comtrade.h"
#include "ui_comtrade.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>
#include <QList>
#include <QMetaType>
#include "config.h"
#include <QtMath>
#include <qcustomplot.h>
#include <QHBoxLayout>
#include <QScrollArea>
#include <readdatafile.h>
#include <fftw3.h>

#define UN 57.735

#define In 5.000

Comtrade::Comtrade(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Comtrade)
{
    ui->setupUi(this);
    f=new fileWidget;
    f->show();
    srcFile=new ComtradeFile;
    sampleFile=new ComtradeFile;
    connect(f,&fileWidget::readSrc,srcFile,&ComtradeFile::readFile);
    connect(f,&fileWidget::readSam,sampleFile,&ComtradeFile::readFile);
    //源稳态
    srcCfgWidegt=new cfgWidget(ui->groupBox1);
    connect(srcFile,&ComtradeFile::signalCFG,srcCfgWidegt,&cfgWidget::displayCfg);
    srcCfgM=new cfgDataModel;
    srcChannelWidget=new ChannelWidget(ui->groupBox2);
    connect(srcFile,&ComtradeFile::signalChan,srcCfgM,&cfgDataModel::setData);
    connect(srcCfgM,&cfgDataModel::signalInit,srcChannelWidget,&ChannelWidget::displayChannel);
    connect(srcChannelWidget,&ChannelWidget::signalType,srcCfgM,&cfgDataModel::getTypeList);
    connect(srcCfgM,&cfgDataModel::signalList,srcChannelWidget,&ChannelWidget::getChannel);
    connect(srcChannelWidget,&ChannelWidget::signalWname,srcCfgM,&cfgDataModel::getCId);
    connect(srcCfgM,&cfgDataModel::signalId,srcFile,&ComtradeFile::getSchart);
    srcSDM=new steadyDataModel;
    srcSWidget=new SteadyWidget(ui->groupBox3);
    connect(srcFile,&ComtradeFile::signalSChart,srcSDM,&steadyDataModel::setData);
    connect(srcSDM,&steadyDataModel::signalChartInfo,srcSWidget,&SteadyWidget::startP);
    connect(srcSDM,&steadyDataModel::signalFFTInfo,srcSWidget,&SteadyWidget::displayFFTInfo);
    connect(srcSWidget,&SteadyWidget::signalWaveTime,srcSDM,&steadyDataModel::CalFFT);

    //试品稳态
    sampCfgWidget=new cfgWidget(ui->groupBox4);
    connect(sampleFile,&ComtradeFile::signalCFG,sampCfgWidget,&cfgWidget::displayCfg);
    sampCfgM=new cfgDataModel;
    sampChannelWidget=new ChannelWidget(ui->groupBox5);
    connect(sampleFile,&ComtradeFile::signalChan,sampCfgM,&cfgDataModel::setData);
    connect(sampCfgM,&cfgDataModel::signalInit,sampChannelWidget,&ChannelWidget::displayChannel);
    connect(sampChannelWidget,&ChannelWidget::signalType,sampCfgM,&cfgDataModel::getTypeList);
    connect(sampCfgM,&cfgDataModel::signalList,sampChannelWidget,&ChannelWidget::getChannel);
    connect(sampChannelWidget,&ChannelWidget::signalWname,sampCfgM,&cfgDataModel::getCId);
    connect(sampCfgM,&cfgDataModel::signalId,sampleFile,&ComtradeFile::getSchart);
    sampSDM=new steadyDataModel;
    sampSWidget=new SteadyWidget(ui->groupBox6);
    connect(sampleFile,&ComtradeFile::signalSChart,sampSDM,&steadyDataModel::setData);
    connect(sampSDM,&steadyDataModel::signalChartInfo,sampSWidget,&SteadyWidget::startP);
    connect(sampSDM,&steadyDataModel::signalFFTInfo,sampSWidget,&SteadyWidget::displayFFTInfo);
    connect(sampSWidget,&SteadyWidget::signalWaveTime,sampSDM,&steadyDataModel::CalFFT);
    //源暂态
    srcCfgWidegt_2=new cfgWidget(ui->groupBox7);
    connect(srcFile,&ComtradeFile::signalCFG,srcCfgWidegt_2,&cfgWidget::displayCfg);
    srcCfgM_2=new cfgDataModel;
    srcChannelWidget_2=new ChannelWidget(ui->groupBox8);
    connect(srcFile,&ComtradeFile::signalChan,srcCfgM_2,&cfgDataModel::setData);
    connect(srcCfgM_2,&cfgDataModel::signalInit,srcChannelWidget_2,&ChannelWidget::displayChannel);
    connect(srcChannelWidget_2,&ChannelWidget::signalType,srcCfgM_2,&cfgDataModel::getTypeList);
    connect(srcCfgM_2,&cfgDataModel::signalList,srcChannelWidget_2,&ChannelWidget::getChannel);
    connect(srcChannelWidget_2,&ChannelWidget::signalWname,srcCfgM_2,&cfgDataModel::getCId);
    connect(srcCfgM_2,&cfgDataModel::signalId,srcFile,&ComtradeFile::getTchart);
    srcTWidget=new TransientWidget(ui->groupBox9);
    srcTDM=new transientDataModel;
    connect(srcFile,&ComtradeFile::signalTChart,srcTDM,&transientDataModel::setData);
    connect(srcTDM,&transientDataModel::signalChartInfo,srcTWidget,&TransientWidget::startP);
    //试品暂态
    sampCfgWidget_2=new cfgWidget(ui->groupBox10);
    connect(sampleFile,&ComtradeFile::signalCFG,sampCfgWidget_2,&cfgWidget::displayCfg);
    sampCfgM_2=new cfgDataModel;
    sampChannelWidget_2=new ChannelWidget(ui->groupBox11);
    connect(sampleFile,&ComtradeFile::signalChan,sampCfgM_2,&cfgDataModel::setData);
    connect(sampCfgM_2,&cfgDataModel::signalInit,sampChannelWidget_2,&ChannelWidget::displayChannel);
    connect(sampChannelWidget_2,&ChannelWidget::signalType,sampCfgM_2,&cfgDataModel::getTypeList);
    connect(sampCfgM_2,&cfgDataModel::signalList,sampChannelWidget_2,&ChannelWidget::getChannel);
    connect(sampChannelWidget_2,&ChannelWidget::signalWname,sampCfgM_2,&cfgDataModel::getCId);
    connect(sampCfgM_2,&cfgDataModel::signalId,sampleFile,&ComtradeFile::getTchart);
    sampTWidget=new TransientWidget(ui->groupBox12);
    sampTDM=new transientDataModel;
    connect(sampleFile,&ComtradeFile::signalTChart,sampTDM,&transientDataModel::setData);
    connect(sampTDM,&transientDataModel::signalChartInfo,sampTWidget,&TransientWidget::startP);

    connect(srcTWidget,&TransientWidget::signalChangedT,sampTWidget,&TransientWidget::signalSetTime);
    connect(sampTWidget,&TransientWidget::signalChangedT,srcTWidget,&TransientWidget::signalSetTime);

    ui->tabWidget->setCurrentIndex(0);
}

Comtrade::~Comtrade()
{
    delete ui;
}













