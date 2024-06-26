#pragma once

#include <QObject>
#include "BaseLogOutput.h"

#include "LogMsgType.h"

class TrollLogOutput : public BaseLogOutput
{
    Q_OBJECT
public:
    explicit TrollLogOutput(QObject *parent = nullptr);

public:
    virtual bool open(const OutputLogUrl &url, const Log::LevelFlags flags);
    virtual bool write(const LogItem &item);

private:
    void write(const LogMsgType lmt, const char *pch);
};
