#pragma once

#include <QtCore/qglobal.h>

#if defined(IBDATA_LIBRARY)
#define IBDATA_EXPORT Q_DECL_EXPORT
#else
#define IBDATA_EXPORT Q_DECL_IMPORT
#endif
