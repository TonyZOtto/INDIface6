#pragma once

#include <QString>
#include <QString>

#include "../eIRbase/AText.h"
#include "../eIRcore/QQFileInfo.h"
#include "FunctionInfo.h"
#include "LogObject.h"

class Context
{
public: // ctors
    Context() {;}
    Context(const char * pchFuncInfo,
            const char * pchFileName,
            const unsigned fileLine,
            const Log::Level lvl);

public: // const
    FunctionInfo functionInfo() const;
    QQFileInfo fileInfo() const;
    unsigned fileLine() const;
    Log::Level level() const;

private:
    AText mQFuncInfo;
    AText mFileName;
    unsigned mFileLine;
    Log::Level mLogLevel;
};
