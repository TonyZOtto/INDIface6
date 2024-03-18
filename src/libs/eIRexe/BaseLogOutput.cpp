#include "BaseLogOutput.h"

BaseLogOutput::BaseLogOutput(QObject *parent) : QObject{parent} {;}

BaseLogOutput::BaseLogOutput(const OutputLogUrl &url,
                             const Log::LevelFlags flags,
                             QObject *parent)
    : QObject(parent)
    , mUrl(url)
    , mOpenMode(QIODevice::NotOpen)
    , mFlags(flags)
{
}

