TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    qlogsystem \
    unit \
    demo

OTHER_FILES += \
    *.prf \
    doc/src/*.dox \
    scripts/*.py \
    *.py \
    qpm.json \
    qmldir \
    com_balabit_qlogsystem.pri \
    com_balabit_qlogsystem.qrc \
    README.md

include(coverage.prf)
include(doxy.prf)
