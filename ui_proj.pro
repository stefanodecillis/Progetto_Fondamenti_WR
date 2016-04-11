#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T14:59:51
#
#-------------------------------------------------
CONFIG += c++11
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ui_proj
TEMPLATE = app


SOURCES += main.cpp\
    input_file.cpp \
    drag_drop.cpp \
    menu.cpp \
    struttura_dati.cpp \
    visualizzaione.cpp \
    qcustomplot.cpp \
    water_reading.cpp \
    interrogazione.cpp \
    analisi.cpp \
    worker.cpp

HEADERS  += input_file.h \
    drag_drop.h \
    water_reading.h \
    menu.h \
    visualizzaione.h \
    struttura_dati.h \
    qcustomplot.h \
    interrogazione.h \
    analisi.h \
    worker.h

FORMS    += \
    drag_drop.ui \
    menu.ui \
    visualizzaione.ui \
    interrogazione.ui \
    analisi.ui


RESOURCES += \
    imgfile.qrc
