#pragma once

#include <QtCore/qglobal.h>

#if defined(IFCORE_LIBRARY)
#define IFCORE_EXPORT Q_DECL_EXPORT
#else
#define IFCORE_EXPORT Q_DECL_IMPORT
#endif
