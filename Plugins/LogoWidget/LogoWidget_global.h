#ifndef LOGOWIDGET_GLOBAL_H
#define LOGOWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOGOWIDGET_LIBRARY)
#  define LOGOWIDGET_API Q_DECL_EXPORT
#else
#  define LOGOWIDGET_API Q_DECL_IMPORT
#endif

#endif // LOGOWIDGET_GLOBAL_H
