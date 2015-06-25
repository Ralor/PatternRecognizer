#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T08:13:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PatternRecognizer
TEMPLATE = app
CONFIG  += c++11

SRC_DIR = ../src
INC_DIR = ../include
LIB_DIR = ../lib
RES_DIR = ../resources
BIN_DIR = ../bin

SOURCES += $${SRC_DIR}/main.cpp \
        $${SRC_DIR}/mainwindow.cpp

HEADERS += $${INC_DIR}/mainwindow.h \
	$${INC_DIR}/cvimagewidget.h \
	$${INC_DIR}/plugin_interfaces.h

FORMS   += $${RES_DIR}/mainwindow.ui

INCLUDEPATH += $${INC_DIR}

LIBS += -L$${LIB_DIR} \
	-lopencv_core300.dll \
	-lopencv_imgproc.dll \
	-lopencv_highgui.dll

DESTDIR = $${BIN_DIR}

QMAKE_POST_LINK = windeployqt $$shell_quote($$shell_path($${BIN_DIR}/$${TARGET}.exe))
