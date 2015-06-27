#-------------------------------------------------
#
# Project created by QtCreator 2015-06-28T03:31:45
#
#-------------------------------------------------

QT       -= gui

TARGET = RectangleRecognizer
TEMPLATE = lib

CONFIG += c++11

DEFINES += RECTANGLERECOGNIZER_LIBRARY

SRC_DIR = $${PWD}/../src
INC_DIR = $${PWD}/../include
LIB_DIR = $${PWD}/../lib
RES_DIR = $${PWD}/../resources
BIN_DIR = $${PWD}/../bin

SOURCES += \
        $${SRC_DIR}/plugins/rectanglerecognizer.cpp

HEADERS += \
        $${INC_DIR}/plugins/rectanglerecognizer.h \
        $${INC_DIR}/plugins/rectanglerecognizer_global.h \
        $${INC_DIR}/plugins/plugin_interfaces.h

INCLUDEPATH += \
        $${INC_DIR} \
        $${INC_DIR}/plugins

LIBS += \
        -L$${LIB_DIR} \
        -lopencv_core300.dll \
        -lopencv_imgproc300.dll \
        -lopencv_highgui300.dll

DESTDIR = $${BIN_DIR}
