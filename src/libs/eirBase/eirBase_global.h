#ifndef EIRBASE_GLOBAL_H
#define EIRBASE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRBASE_LIBRARY)
#define EIRBASE_EXPORT Q_DECL_EXPORT
#else
#define EIRBASE_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRBASE_GLOBAL_H
