#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T14:59:51
#
#-------------------------------------------------
CONFIG += c++11
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ui_proj
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    input_file.cpp \
    drag_drop.cpp \
    water_reading.cpp

HEADERS  += mainwindow.h \
    input_file.h \
    drag_drop.h \
    water_reading.h

FORMS    += \
    drag_drop.ui \
    mainwindow.ui

RESOURCES += \
    imgfile.qrc
