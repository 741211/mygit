#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include <QWidget>
#include "comtradefile.h"
namespace Ui {
class ChannelWidget;
}
class ChannelWidget : public QWidget
{
    Q_OBJECT

public:
    int numChart;
    QList<Chart> channelList;
    bool checked;
    explicit ChannelWidget(QWidget *parent = 0);
    ~ChannelWidget();
signals:
    void signalType(QString& s);
    void signalWname(const QString& s);
public slots:
    void displayChannel(QList<QString> nrateList,QList<Chart> chartList);
    void setChannel();
    void getChannel(QList<QString> list);
    void getWaveName(const QString &s);
private:
    Ui::ChannelWidget *ui;
};

#endif // CHANNELWIDGET_H
