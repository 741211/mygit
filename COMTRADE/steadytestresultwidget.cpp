#include "steadytestresultwidget.h"
#include "ui_steadytestresultwidget.h"

steadyTestResultWidget::steadyTestResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::steadyTestResultWidget)
{
    ui->setupUi(this);
}

steadyTestResultWidget::~steadyTestResultWidget()
{
    delete ui;
}
