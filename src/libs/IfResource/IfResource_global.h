#pragma once

#include <QtCore/qglobal.h>

#if defined(IFRESOURCE_LIBRARY)
#define IFRESOURCE_EXPORT Q_DECL_EXPORT
#else
#define IFRESOURCE_EXPORT Q_DECL_IMPORT
#endif
