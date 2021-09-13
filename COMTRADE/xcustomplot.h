#ifndef XCUSTOMPLOT_H
#define XCUSTOMPLOT_H
#include "qcustomplot.h"
#include <QObject>
#include <QList>

class XcustomPlot : public QCustomPlot
{
    Q_OBJECT

public:
    enum SeclectType{
        redLine=1,
        blueLine=2
    };
    Q_ENUM(SeclectType)

    explicit XcustomPlot(QWidget *parent = 0);
    bool press;
    bool changed;
    int cntEvent;
    SeclectType LineType;
    QCPItemTracer *redTracer,*blueTracer;
public slots:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent *e);

signals:
    void signalPoint(SeclectType LineType, double x);

private:
    //Ui::XcustomPlot *ui;
};

#endif // XCUSTOMPLOT_H
