#ifndef APPLAYOUT_GLOBAL_H
#define APPLAYOUT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(APPLAYOUT_LIBRARY)
#  define APPLAYOUT_API Q_DECL_EXPORT
#else
#  define APPLAYOUT_API Q_DECL_IMPORT
#endif

#endif // APPLAYOUT_GLOBAL_H
