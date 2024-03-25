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
    BaseLogOutput(const OutputLogUrl &url, const Log::LevelFlags flags, QObject *parent = nullptr);

public:
    virtual bool open(const OutputLogUrl &url, const Log::LevelFlags flags) = 0;
    virtual bool write(const LogItem &item) = 0;

signals:

protected:
    OutputLogUrl mUrl;
    QIODevice::OpenMode mOpenMode=QIODevice::NotOpen;
    Log::LevelFlags mFlags;
};
