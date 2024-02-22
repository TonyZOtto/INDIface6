#pragma once

#include <QtCore/qglobal.h>

#if defined(IFFACE_LIBRARY)
#define IFFACE_EXPORT Q_DECL_EXPORT
#else
#define IFFACE_EXPORT Q_DECL_IMPORT
#endif
