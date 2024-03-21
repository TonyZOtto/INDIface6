#pragma once

#include "LogItem.h"
#include "Logger.h"
#include "LogObject.h"
#include "LogMacros.h"

Q_GLOBAL_STATIC(Logger, LOG);

#define WEXPECTEQ(exp, act) LOGEXPECT(TWarning, Log::Equals, exp, act)
#define TEXPECTEQ(exp, act) LOGEXPECT(TWarning, Log::Equals, exp, act)
#define FEXPECTEQ(exp, act) LOGEXPECT(TWarning, Log::Equals, exp, act)

#define PREFER(bexp) LOGASSERT(Prefer, AssertTrue, bexp)
#define PREFERNOT(bexp) LOGASSERT(Prefer, AssertFalse, bexp)
