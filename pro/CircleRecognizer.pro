#-------------------------------------------------
#
# Project created by QtCreator 2015-06-28T03:29:30
#
#-------------------------------------------------

QT       -= gui

TARGET = CircleRecognizer
TEMPLATE = lib

CONFIG += c++11

DEFINES += CIRCLERECOGNIZER_LIBRARY

SRC_DIR = $${PWD}/../src
INC_DIR = $${PWD}/../include
LIB_DIR = $${PWD}/../lib
RES_DIR = $${PWD}/../resources
BIN_DIR = $${PWD}/../bin

SOURCES += \
        $${SRC_DIR}/plugins/circlerecognizer.cpp

HEADERS += \
        $${INC_DIR}/plugins/circlerecognizer.h \
        $${INC_DIR}/plugins/circlerecognizer_global.h \
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
