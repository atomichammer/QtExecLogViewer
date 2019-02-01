#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T16:52:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExecLog
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    csvreader.cpp

HEADERS  += mainwindow.h \
    csvreader.h

FORMS    += mainwindow.ui
