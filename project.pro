TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    qlogsystem \
    unit \
    demo

OTHER_FILES += \
    *.prf \
    doc/src/*.dox

include(coverage.prf)
include(doxy.prf)
