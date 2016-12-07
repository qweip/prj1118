#-------------------------------------------------
#
# Project created by QtCreator 2016-11-18T15:55:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prj1118
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ConnA.cpp

HEADERS  += mainwindow.h \
    ConnA.hpp \
    sniff.hpp

FORMS    += mainwindow.ui

QT += network

win32 {
#------------wpcap---------------
    INCLUDEPATH += ./Include/wpcap
    LIBS += ./Lib/wpcap.lib
    LIBS += -l ws2_32
}

unix:!macx {
#------------wpcap---------------
  LIBS += -lpcap
}