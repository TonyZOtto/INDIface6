#pragma once

#include <QObject>

#include "OutputLogUrl.h"
#include "LogObject.h"

class BaseLogOutput : public QObject
{
    Q_OBJECT
public: // ctors
    explicit BaseLogOutput(QObject *parent = nullptr);
    BaseLogOutput(const OutputLogUrl &url, const Log::LevelFlags flags, QObject *parent = nullptr);

public:
    virtual bool open(const OutputLogUrl &url) = 0;

signals:

private:
    OutputLogUrl mUrl;
    QIODevice::OpenMode mOpenMode=QIODevice::NotOpen;
    Log::LevelFlags mFlags;
};
