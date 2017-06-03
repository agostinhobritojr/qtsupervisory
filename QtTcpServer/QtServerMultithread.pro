#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T08:02:34
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtServerMultithread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myserver.cpp \
    mythread.cpp \
    datastorage.cpp

HEADERS  += mainwindow.h \
    myserver.h \
    mythread.h \
    datastorage.h

FORMS    += mainwindow.ui
