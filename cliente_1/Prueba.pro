#-------------------------------------------------
#
# Project created by QtCreator 2017-06-01T00:13:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Prueba
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogcompra.cpp \
    socketclient.cpp

HEADERS  += mainwindow.h \
    dialogcompra.h \
    socketclient.h

FORMS    += mainwindow.ui \
    dialogcompra.ui
