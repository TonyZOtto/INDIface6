#pragma once

#include "Context.h"

#define LOGCTX() Context(Q_FILE_INFO, __FILE__, __LINE__)
#define LOGITEM(msg) LogItem(LOGCTX, msg);
#define LOGITEM1(fmt, arg1, arg2, arg3, arg4) LogItem(LOGCTX, fmt, #arg1, arg1);
#define LOGITEM2(fmt, arg1, arg2, arg3, arg4) LogItem(LOGCTX, fmt, #arg1, arg1, #arg2, arg2);
#define LOGITEM3(fmt, arg1, arg2, arg3, arg4) LogItem(LOGCTX, fmt, #arg1, arg1, #arg2, arg2, #arg3, arg3);
#define LOGITEM4(fmt, arg1, arg2, arg3, arg4) LogItem(LOGCTX, fmt, #arg1, arg1, #arg2, arg2, #arg3, arg3, #arg4, arg4);
#define LOGADD(item)
