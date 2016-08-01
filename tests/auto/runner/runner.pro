#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T15:21:44
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_runnertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../../pandoc-slave/pandoc-slave/pandoc-slave.pri)

SOURCES += tst_runnertest.cpp
