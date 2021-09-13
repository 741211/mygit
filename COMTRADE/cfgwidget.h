#ifndef CFGWIDGET_H
#define CFGWIDGET_H

#include "config.h"

#include <QWidget>

namespace Ui {
class cfgWidget;
}

class cfgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit cfgWidget(QWidget *parent = 0);
    ~cfgWidget();
public slots:
    void displayCfg(const Config *cfgFile,const QString &aFileName);
private:
    Ui::cfgWidget *ui;
};

#endif // CFGWIDGET_H
