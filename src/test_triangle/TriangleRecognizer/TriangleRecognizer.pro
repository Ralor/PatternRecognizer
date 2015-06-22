#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T08:59:12
#
#-------------------------------------------------

QT       -= gui

TARGET = TriangleRecognizer
TEMPLATE = lib

CONFIG += release
CONFIG += c++11

DEFINES += TRIANGLERECOGNIZER_LIBRARY

SOURCES += trianglerecognizer.cpp

HEADERS += trianglerecognizer.h \
        trianglerecognizer_global.h \
    ../../test_gui/PatternRecognizer/plugin_interfaces.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../../test_gui/PatternRecognizer/ \
               C:/opencv/build/x86/mingw/install/include

LIBS += "C:/opencv/build/x86/mingw/install/x86/mingw/lib/*.a"

OTHER_FILES += \
    trianglerecognizer.json

