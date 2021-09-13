#-------------------------------------------------
#
# Project created by QtCreator 2021-06-22T09:45:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = COMTRADE
TEMPLATE = app


SOURCES += main.cpp\
        comtrade.cpp \
    config.cpp \
    qcustomplot.cpp \
    xcustomplot.cpp \
    readdatafile.cpp \
    fthreadwork.cpp \
    wavewidget.cpp \
    filewidget.cpp \
    comtradefile.cpp \
    cfgwidget.cpp \
    channelwidget.cpp \
    steadywidget.cpp \
    cfgdatamodel.cpp \
    steadydatamodel.cpp \
    transientwidget.cpp \
    transientdatamodel.cpp \
    steadytestresultwidget.cpp \
    steadytestresultdata.cpp

HEADERS  += comtrade.h \
    config.h \
    qcustomplot.h \
    xcustomplot.h \
    readdatafile.h \
    fftw3.h \
    fthreadwork.h \
    wavewidget.h \
    filewidget.h \
    comtradefile.h \
    cfgwidget.h \
    channelwidget.h \
    steadywidget.h \
    cfgdatamodel.h \
    steadydatamodel.h \
    transientwidget.h \
    transientdatamodel.h \
    steadytestresultwidget.h \
    steadytestresultdata.h

FORMS    += comtrade.ui \
    wavewidget.ui \
    filewidget.ui \
    cfgwidget.ui \
    channelwidget.ui \
    steadywidget.ui \
    transientwidget.ui \
    steadytestresultwidget.ui

RESOURCES +=

DISTFILES +=

LIBS  +=  FFT/libfftw3-3.lib
LIBS  +=  FFT/libfftw3-3.dll
