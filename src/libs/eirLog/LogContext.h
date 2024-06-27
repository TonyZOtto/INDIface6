#pragma once

#include <QSharedDataPointer>
#include <QMessageLogContext>

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
