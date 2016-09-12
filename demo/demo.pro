QT       += core
QT       -= gui

TARGET = qlogsystem-demo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cc

include(../common.prf)

target.path = $$BINDIR
INSTALLS += target

INCLUDEPATH += $${IN_PWD}/../qlogsystem/

LIBS += -L$${OUT_PWD}/../qlogsystem -lqlogsystem
