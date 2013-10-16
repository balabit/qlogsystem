#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T11:12:52
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_threadsafetytest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_threadsafetytest.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../testcommon.prf)
