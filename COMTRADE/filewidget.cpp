#include "filewidget.h"
#include "ui_filewidget.h"
#include <QDir>
#include <QFileDialog>


fileWidget::fileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileWidget)
{
    ui->setupUi(this);

}

fileWidget::~fileWidget()
{
    delete ui;
}

void fileWidget::on_srcBtn_clicked()
{
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="打开一个文件"; //对话框标题
    QString filter="程序文件(*.cfg);;所有文件(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);

    if (aFileName.isEmpty())
        return;
    emit readSrc(aFileName);
}

void fileWidget::on_samBtn_clicked()
{
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="打开一个文件"; //对话框标题
    QString filter="程序文件(*.cfg);;所有文件(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);

    if (aFileName.isEmpty())
        return;
    emit readSam(aFileName);
}
