#include "transientwidget.h"
#include "ui_transientwidget.h"

TransientWidget::TransientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransientWidget)
{
    ui->setupUi(this);
    wave=new WaveWidget;
    h=new QHBoxLayout(ui->groupBox);
    h->addWidget(wave);
    connect(wave,&WaveWidget::signalT,this,&TransientWidget::signalChangedT);
    connect(this,&TransientWidget::signalSetTime,wave,&WaveWidget::setTime);
    connect(this,&TransientWidget::startP,wave,&WaveWidget::init);
}

TransientWidget::~TransientWidget()
{
    delete ui;
}

