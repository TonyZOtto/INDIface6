#pragma once

#include <QObject>

#include "Log.h"
#include "OutputLogUrl.h"

class BaseLogOutput : public QObject
{
    Q_OBJECT
public:
    explicit BaseLogOutput(QObject *parent = nullptr);
    BaseLogOutput(const OutputLogUrl &url, const Log::LevelFlags flags, QObject *parent = nullptr);

signals:

private:
    OutputLogUrl mUrl;
    Log::LevelFlags mLevelFlags;
};
