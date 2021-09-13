#include "comtrade.h"
#include <QApplication>
#include <filewidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Comtrade w;
    w.show();

    return a.exec();
}
