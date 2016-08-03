QT += core
QT -= gui

CONFIG += console c++14
CONFIG -= app_bundle

include(pandoc-slave/pandoc-slave.pri)

TARGET = pandoc-slave

TEMPLATE = app

SOURCES += main.cpp
