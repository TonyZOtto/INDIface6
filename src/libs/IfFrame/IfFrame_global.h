#pragma once

#include <QtCore/qglobal.h>

#if defined(IFFRAME_LIBRARY)
#define IFFRAME_EXPORT Q_DECL_EXPORT
#else
#define IFFRAME_EXPORT Q_DECL_IMPORT
#endif
