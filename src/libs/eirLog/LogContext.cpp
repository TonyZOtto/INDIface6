#include "LogContext.h"

#include <QFileInfo>
#include <QString>

#include "../eIRbase/Types.h"

class LogContextData : public QSharedData
{
public:
    EpochMilliseconds   d_TimestampEms;
    QString             d_QFuncInfo;
    QFileInfo           d_FileInfo;
    int                 d_FileLine;
    QString             d_CategoryName;
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
