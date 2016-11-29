#-------------------------------------------------
#
# Project created by QtCreator 2016-09-07T08:44:22
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videogui
TEMPLATE = app

CONFIG += mobility
MOBILITY = multimedia


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    database.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc \
    icons.qrc
