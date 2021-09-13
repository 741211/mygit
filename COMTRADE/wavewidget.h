#ifndef WAVEWIDGET_H
#define WAVEWIDGET_H
#include "config.h"
#include "fthreadwork.h"
#include "xcustomplot.h"

#include <QWidget>

namespace Ui {
class WaveWiget;
}

struct Chart;
class WaveWidget : public QWidget
{
    Q_OBJECT

public:

    double width,length,Xmin,Xmax,Ymax,Ymin,lengthMin;
    QString Yunit;
    double pixel1;
    void getPixel1();
    explicit WaveWidget(QWidget *parent = 0);
    ~WaveWidget();
public slots:
    void init(QVector<double> xData, QVector<double> yData,const QString& Yunit);
    void getTime();
    void setTime(const double& t1,const double& t2);
private slots:
    void on_expansion_clicked();

    void on_reduction_clicked();

    void on_xE_clicked();

    void on_xR_clicked();

    void on_LMove_clicked();

    void on_RMove_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_yE_clicked();

    void on_yR_clicked();

signals:
    void signalT(const double& t1,const double& t2);

private:
    Ui::WaveWiget *ui;
};

#endif // WAVEWIDGET_H
