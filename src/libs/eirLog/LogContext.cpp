#include "LogContext.h"

class LogContextData : public QSharedData
{
public:
};

LogContext::LogContext()
    : data(new LogContextData)
{}

LogContext::LogContext(const LogContext &rhs)
    : data{rhs.data}
{}

LogContext &LogContext::operator=(const LogContext &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

LogContext::~LogContext() {}
