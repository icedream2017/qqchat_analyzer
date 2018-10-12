#-------------------------------------------------
#
# Project created by QtCreator 2017-12-02T23:41:08
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqcr_analyzer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    textprocessor.cpp \
    database.cpp \
    textanalyzer.cpp

HEADERS  += widget.h \
    textprocessor.h \
    database.h \
    textanalyzer.h

FORMS    += widget.ui
