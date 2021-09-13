#ifndef STEADYTESTRESULTWIDGET_H
#define STEADYTESTRESULTWIDGET_H

#include <QWidget>

namespace Ui {
class steadyTestResultWidget;
}

class steadyTestResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit steadyTestResultWidget(QWidget *parent = 0);
    ~steadyTestResultWidget();

private:
    Ui::steadyTestResultWidget *ui;
};

#endif // STEADYTESTRESULTWIDGET_H
