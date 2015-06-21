#-------------------------------------------------
#
# Project created by QtCreator 2015-06-20T22:38:12
#
#-------------------------------------------------

QT       -= gui

TARGET = adder
TEMPLATE = lib

CONFIG += release

DEFINES += ADDER_LIBRARY

SOURCES += adder.cpp

HEADERS += adder.h\
        adder_global.h

INCLUDEPATH += "C:/dev/PatternRecognizer/include"

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    adderplugin.json
