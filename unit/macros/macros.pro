#-------------------------------------------------
#
# Project created by QtCreator 2013-10-11T09:51:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_macrostest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_macrostest.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../testcommon.prf)
