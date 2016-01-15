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
    cwater_reading.cpp \
    input_file.cpp \
    drag_drop.cpp \
    manage_wr.cpp

HEADERS  += mainwindow.h \
    cwater_reading.h \
    input_file.h \
    drag_drop.h \
    manage_wr.h

FORMS    += \
    drag_drop.ui \
    mainwindow.ui

RESOURCES += \
    imgfile.qrc
