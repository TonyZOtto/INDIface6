#include "Context.h"


Context::Context(const char *pchFuncInfo, const char *pchFileName,
                 const unsigned int fileLine, const LogLevel lvl)
{
    mQFuncInfo = pchFuncInfo, mFileName = pchFileName,
    mFileLine = fileLine, mLogLevel = lvl;
}

FunctionInfo Context::functionInfo() const
{
    return FunctionInfo(mQFuncInfo);
}

QQFileInfo Context::fileInfo() const
{
    return QQFileInfo(mFileName.toString());
}

unsigned int Context::fileLine() const
{
    return mFileLine;
}

Log::Level Context::level() const
{
    return mLogLevel;
}
