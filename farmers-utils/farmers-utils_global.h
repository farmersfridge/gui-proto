#ifndef FARMERSUTILS_GLOBAL_H
#define FARMERSUTILS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FARMERSUTILS_LIBRARY)
#  define FARMERSUTILSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FARMERSUTILSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FARMERSUTILS_GLOBAL_H
