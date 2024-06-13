#pragma once

#include <QObject>
#include "BaseLogOutput.h"

#include "LogMsgType.h"

class TrollLogOutput : public BaseLogOutput
{
    Q_OBJECT
public:
    explicit TrollLogOutput(const OutputLogUrl &url, QObject *parent = nullptr);

public:
    virtual bool open(const OutputLogUrl &url) override;
    virtual bool write(const LogItem &item) override;

private:
    void write(const LogMsgType lmt, const QString &s);
    void write(const LogMsgType lmt, const char *pch);
};
