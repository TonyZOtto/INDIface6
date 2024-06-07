#pragma once

#include <QObject>
#include "BaseLogOutput.h"

class FileLogOutput : public BaseLogOutput
{
    Q_OBJECT
public:
    explicit FileLogOutput(QObject *parent = nullptr);

public: // virtual
    virtual bool open(const OutputLogUrl &url, const Log::LevelFlags flags);
    virtual bool write(const LogItem &item);

private:
    void write(const LogMsgType lmt, const QString &s);
    void write(const LogMsgType lmt, const char *pch);

};
