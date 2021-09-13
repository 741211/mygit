#include "cfgwidget.h"
#include "ui_cfgwidget.h"

cfgWidget::cfgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cfgWidget)
{
    ui->setupUi(this);
}

cfgWidget::~cfgWidget()
{
    delete ui;
}

void cfgWidget::displayCfg(const Config *cfgFile, const QString &aFileName)
{
    QString name=aFileName.left(aFileName.length()-3).append("cfg");
    ui->text1->setText(name);
    ui->text2->setText(aFileName);
    ui->text3->setText(cfgFile->station_name);
    ui->text4->setText(cfgFile->rec_dev__id);
    ui->text5->setText(QString::number(cfgFile->Anum));
    ui->text6->setText(QString::number(cfgFile->Dnum));
    ui->text7->setText(QString::number(cfgFile->waveLength,'f', 3));
    ui->text8->setText(QString::number(cfgFile->IF,'f', 3));
    ui->text9->setText(cfgFile->firstTime.date1+","+cfgFile->firstTime.date2);
    ui->text10->setText(cfgFile->secondTime.date1+","+cfgFile->secondTime.date2);
}
