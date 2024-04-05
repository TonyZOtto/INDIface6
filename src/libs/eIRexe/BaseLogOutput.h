#pragma once

#include <QObject>

#include "OutputLogUrl.h"
#include "LogObject.h"
class LogItem;

class BaseLogOutput : public QObject
{
    Q_OBJECT
public: // ctors
    explicit BaseLogOutput(QObject *parent = nullptr);
protected:
    BaseLogOutput(const OutputLogUrl &url, const Log::LevelFlags flags, QObject *parent = nullptr);

public:
    virtual bool open(const OutputLogUrl &url, const Log::LevelFlags flags) = 0;
    virtual bool write(const LogItem &item) = 0;
    void url(const OutputLogUrl u);
    void mode(const QIODevice::OpenMode m);
    void flags(const Log::LevelFlags f);

signals:

protected:
    OutputLogUrl mUrl;
    QIODevice::OpenMode mOpenMode=QIODevice::NotOpen;
    Log::LevelFlags mLevelFlags;
};

inline void BaseLogOutput::mode(const QIODeviceBase::OpenMode m)
{
    mOpenMode = m;
}
