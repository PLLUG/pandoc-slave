#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T09:36:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_buildertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../includes/default.pri)
include(../../../pandoc-slave/pandoc-slave/pandoc-slave.pri)

SOURCES += tst_buildertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
