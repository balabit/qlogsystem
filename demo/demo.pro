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

windows {
  debug {
    build_path = $${OUT_PWD}/../qlogsystem/debug
  } else {
    build_path = $${OUT_PWD}/../qlogsystem/release
  }
} else {
  build_path = $${OUT_PWD}/../qlogsystem
}

LIBS += -L$${build_path} -lqlogsystem
