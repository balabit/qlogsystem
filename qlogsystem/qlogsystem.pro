QT       += core
QT       -= gui

TARGET = qlogsystem

TEMPLATE = lib

DEFINES += QLOGSYSTEM_LIBRARY

SOURCES += \
    logger.cc \
    manager.cc \
    standardlogformatter.cc \
    timestampedstandardlogformatter.cc \
    iodeviceoutput.cc

HEADERS += \
    manager.hh \
    logformatter.hh \
    logger.hh \
    loglevels.hh \
    standardlogformatter.hh \
    timestampedstandardlogformatter.hh \
    iodeviceoutput.hh \
    logoutput.hh \
    qlogsystem.hh \
    loghelpers.hh \
    qlogsystem_global.hh

QMAKE_PKGCONFIG_DESCRIPTION = Logging library for Qt
include(../libinstall.prf)
