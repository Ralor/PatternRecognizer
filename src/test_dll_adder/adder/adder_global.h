#ifndef ADDER_GLOBAL_H
#define ADDER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ADDER_LIBRARY)
#  define ADDERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ADDERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ADDER_GLOBAL_H
