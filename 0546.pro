#-------------------------------------------------
#
# Project created by QtCreator 2018-05-03T22:12:58
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET = Wireless-node_V2.4.7.20201016_Alpha-DataService-UART
TEMPLATE = app

INCLUDEPATH += "C:/Program Files (x86)/mysql-8.0.16-winx64/mysql-8.0.16-winx64/include"
LIBS+= "C:/Program Files (x86)/mysql-8.0.16-winx64/mysql-8.0.16-winx64/lib/libmysql.lib"

SOURCES += main.cpp\
        widget.cpp \
    form.cpp \
    qcustomplot.cpp

HEADERS  += widget.h \
    form.h \
    qcustomplot.h \
    thesql.h

FORMS    += widget.ui \
    form.ui
CONFIG +=c++11

RESOURCES +=
