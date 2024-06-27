#include "LogItem.h"

#include <QString>
#include <QStringList>

#include "../eIRbase/Types.h"

#include "Log.h"
#include "LogContext.h"

class LogItemData : public QSharedData
{
public:
    LogContext              d_Context;
    Log::Level              d_Level;
    Log::LevelFlags         d_Flags;
    EpochMilliseconds       d_TimestampEms;
    Index                   d_Sequence;
    QString                 d_Message;
    QString                 d_Format;
    QStringList             d_OutputStrings;
    Log::ArgumentInfoList   d_Arguments;
    QString                 d_DebugHead;
    QStringList             d_DebugStrings;
    QString                 d_DebugFoot;
};

LogItem::LogItem()
    : data(new LogItemData)
{}

LogItem::LogItem(const LogItem &rhs)
    : data{rhs.data}
{}

LogItem &LogItem::operator=(const LogItem &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

LogItem::~LogItem() {}
