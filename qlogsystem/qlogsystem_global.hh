#ifndef QLOGSYSTEM_GLOBAL_HH
#define QLOGSYSTEM_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(QLOGSYSTEM_LIBRARY)
#  define QLOGSYSTEMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QLOGSYSTEMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QLOGSYSTEM_GLOBAL_HH
