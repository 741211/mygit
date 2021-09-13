#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include "config.h"
#include <QWidget>

namespace Ui {
class fileWidget;
}

class fileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit fileWidget(QWidget *parent = 0);
    ~fileWidget();
signals:
    void readSrc(const QString &aFileName);
    void readSam(const QString &aFileName);
private slots:
    void on_srcBtn_clicked();

    void on_samBtn_clicked();

private:
    Ui::fileWidget *ui;
};

#endif // FILEWIDGET_H
