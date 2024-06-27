#pragma once

#include <QSharedDataPointer>

class LogItemData;

class LogItem
{
public:
    LogItem();
    LogItem(const LogItem &);
    LogItem &operator=(const LogItem &);
    ~LogItem();

private:
    QSharedDataPointer<LogItemData> data;
};
