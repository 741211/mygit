#ifndef TRANSIENTWIDGET_H
#define TRANSIENTWIDGET_H

#include "wavewidget.h"
#include <QHBoxLayout>
#include <QWidget>

namespace Ui {
class TransientWidget;
}

class TransientWidget : public QWidget
{
    Q_OBJECT

public:
    WaveWidget *wave;
    QHBoxLayout *h;
    explicit TransientWidget(QWidget *parent = 0);
    ~TransientWidget();
signals:
    void signalChangedT(const double& t1,const double& t2);
    void signalSetTime(const double& t1,const double& t2);
    void startP(QVector<double> xData, QVector<double> yData, const QString &unit);
private:
    Ui::TransientWidget *ui;
};

#endif // TRANSIENTWIDGET_H
