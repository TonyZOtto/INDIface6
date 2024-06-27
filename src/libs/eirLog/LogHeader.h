#pragma once

#include <QSharedDataPointer>

class LogHeaderData;

class LogHeader
{
public:
    LogHeader();
    LogHeader(const LogHeader &);
    LogHeader &operator=(const LogHeader &);
    ~LogHeader();

private:
    QSharedDataPointer<LogHeaderData> data;
};
