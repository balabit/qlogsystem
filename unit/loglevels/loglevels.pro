#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T10:56:36
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_loglevelstest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_loglevelstest.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../../testcommon.prf)
