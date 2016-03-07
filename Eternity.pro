#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T16:03:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Eternity
TEMPLATE = app


SOURCES += main.cpp\
    Model/instance_model.cpp \
    Model/piece_model.cpp \
    Tools/string_tools.cpp \
    Model/configuration_model.cpp

HEADERS  += \
    Model/instance_model.h \
    Model/piece_model.h \
    Tools/string_tools.h \
    Model/configuration_model.h

OTHER_FILES += \
    tmp.txt
