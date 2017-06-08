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
    socketclient.cpp \
    widgetprofundidad.cpp \
    dialogclientenuevo.cpp \
    dialogconsulta.cpp

HEADERS  += mainwindow.h \
    dialogcompra.h \
    socketclient.h \
    widgetprofundidad.h \
    dialogclientenuevo.h \
    dialogconsulta.h

FORMS    += mainwindow.ui \
    dialogcompra.ui \
    widgetprofundidad.ui \
    dialogclientenuevo.ui \
    dialogconsulta.ui
