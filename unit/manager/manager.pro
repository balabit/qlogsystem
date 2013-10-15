#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T10:54:43
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_managertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_managertest.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../testcommon.prf)
