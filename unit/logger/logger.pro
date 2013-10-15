#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T10:42:40
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_loggertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_loggertest.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../testcommon.prf)
