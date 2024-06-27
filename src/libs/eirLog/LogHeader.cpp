#include "LogHeader.h"

class LogHeaderData : public QSharedData
{
public:
};

LogHeader::LogHeader()
    : data(new LogHeaderData)
{}

LogHeader::LogHeader(const LogHeader &rhs)
    : data{rhs.data}
{}

LogHeader &LogHeader::operator=(const LogHeader &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

LogHeader::~LogHeader() {}
