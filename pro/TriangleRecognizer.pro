#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T08:59:12
#
#-------------------------------------------------

QT       -= gui

TARGET = TriangleRecognizer
TEMPLATE = lib

CONFIG += c++11

DEFINES += TRIANGLERECOGNIZER_LIBRARY

SRC_DIR = ../src
INC_DIR = ../include
LIB_DIR = ../lib
RES_DIR = ../resources
BIN_DIR = ../bin

SOURCES += \
	$${SRC_DIR}/trianglerecognizer.cpp

HEADERS += \
	$${INC_DIR}/plugins/trianglerecognizer.h \
        $${INC_DIR}/plugins/trianglerecognizer_global.h \
	$${INC_DIR}/plugins/plugin_interfaces.h

INCLUDEPATH += \
	$${INC_DIR} \
	$${INC_DIR}/plugins

LIBS += \
	-L$${LIB_DIR} \
	-lopencv_core300.dll \
	-lopencv_imgproc300.dll \
	-lopencv_highgui300.dll

DESTDIR = $${BIN_DIR}/plugins

OTHER_FILES += \
	$${RES_DIR}/trianglerecognizer.json

