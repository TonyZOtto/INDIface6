#pragma once

#include <QSharedDataPointer>

class LogContextData;

class LogContext
{
public:
    LogContext();
    LogContext(const LogContext &);
    LogContext &operator=(const LogContext &);
    ~LogContext();

private:
    QSharedDataPointer<LogContextData> data;
};
