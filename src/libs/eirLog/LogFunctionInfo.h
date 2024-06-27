#pragma once

#include <QSharedDataPointer>

class LogFunctionInfoData;

class LogFunctionInfo
{
public:
    LogFunctionInfo();
    LogFunctionInfo(const LogFunctionInfo &);
    LogFunctionInfo &operator=(const LogFunctionInfo &);
    ~LogFunctionInfo();

private:
    QSharedDataPointer<LogFunctionInfoData> data;
};
