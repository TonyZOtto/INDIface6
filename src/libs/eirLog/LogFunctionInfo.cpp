#include "LogFunctionInfo.h"

#include <QFileInfo>
#include <QString>

class LogFunctionInfoData : public QSharedData
{
public:
    QString         d_QFuncInfo;
};

LogFunctionInfo::LogFunctionInfo()
    : data(new LogFunctionInfoData)
{}

LogFunctionInfo::LogFunctionInfo(const LogFunctionInfo &rhs)
    : data{rhs.data}
{}

LogFunctionInfo &LogFunctionInfo::operator=(const LogFunctionInfo &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

LogFunctionInfo::~LogFunctionInfo() {}
