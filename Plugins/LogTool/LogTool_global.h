#ifndef LOGTOOL_GLOBAL_H
#define LOGTOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOGTOOL_LIBRARY)
#  define LOGTOOL_API Q_DECL_EXPORT
#else
#  define LOGTOOL_API Q_DECL_IMPORT
#endif

#endif // LOGTOOL_GLOBAL_H
