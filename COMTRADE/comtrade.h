#ifndef COMTRADE_H
#define COMTRADE_H

#include "cfgdatamodel.h"
#include "cfgwidget.h"
#include "channelwidget.h"
#include "comtradefile.h"
#include "filewidget.h"
#include "steadydatamodel.h"
#include "steadywidget.h"
#include "transientdatamodel.h"
#include "transientwidget.h"

#include <QMainWindow>
#include <QList>
#include <config.h>
#include <QLabel>
#include <QMetaType>
#include <config.h>
#include <readdatafile.h>
#include <fthreadwork.h>
#include <wavewidget.h>
namespace Ui {
class Comtrade;
}
class Comtrade : public QMainWindow
{
    Q_OBJECT
public:
    fileWidget *f;
    ComtradeFile *srcFile,*sampleFile;
    cfgWidget *srcCfgWidegt,*sampCfgWidget,*srcCfgWidegt_2,*sampCfgWidget_2;
    cfgDataModel *srcCfgM,*sampCfgM,*srcCfgM_2,*sampCfgM_2;
    ChannelWidget *srcChannelWidget,*sampChannelWidget,*srcChannelWidget_2,*sampChannelWidget_2;
    SteadyWidget *srcSWidget,*sampSWidget;
    steadyDataModel *srcSDM,*sampSDM;
    TransientWidget *srcTWidget,*sampTWidget;
    transientDataModel *srcTDM,*sampTDM;
    explicit Comtrade(QWidget *parent = 0);
    ~Comtrade();

public slots:


signals:


private slots:




private:
    Ui::Comtrade *ui;

};

#endif // COMTRADE_H
