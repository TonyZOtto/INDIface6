#pragma once

#include <QtCore/qglobal.h>

#if defined(IFANALYTICS_LIBRARY)
#define IFANALYTICS_EXPORT Q_DECL_EXPORT
#else
#define IFANALYTICS_EXPORT Q_DECL_IMPORT
#endif
