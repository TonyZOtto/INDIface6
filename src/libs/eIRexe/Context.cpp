#include "Context.h"


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
