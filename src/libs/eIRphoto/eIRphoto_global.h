#pragma once

#include <QtCore/qglobal.h>

#if defined(EIRPHOTO_LIBRARY)
#define EIRPHOTO_EXPORT Q_DECL_EXPORT
#else
#define EIRPHOTO_EXPORT Q_DECL_IMPORT
#endif
