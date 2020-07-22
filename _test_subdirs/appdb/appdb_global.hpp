#ifndef APPDB_GLOBAL_HPP
#define APPDB_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(APPDB_LIBRARY)
#  define APPDBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define APPDBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // APPDB_GLOBAL_HPP
