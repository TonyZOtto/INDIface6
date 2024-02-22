#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRCV_LIBRARY)
#define EIRCV_EXPORT Q_DECL_EXPORT
#else
#define EIRCV_EXPORT Q_DECL_IMPORT
#endif
