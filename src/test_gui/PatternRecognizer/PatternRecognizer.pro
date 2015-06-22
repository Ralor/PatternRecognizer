#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T08:13:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PatternRecognizer
TEMPLATE = app

CONFIG   += c++11
CONFIG   += release

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    cvimagewidget.h \
    plugin_interfaces.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:/opencv/build/x86/mingw/install/include

LIBS += "C:/opencv/build/x86/mingw/install/x86/mingw/lib/*.a"
