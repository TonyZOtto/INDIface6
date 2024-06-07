#include "FileLogOutput.h"

FileLogOutput::FileLogOutput(QObject *parent)
    : BaseLogOutput{parent}
{}

bool FileLogOutput::open(const OutputLogUrl &url, const Log::LevelFlags flags)
{
    Q_ASSERT("!MUSTDO"); // MUSTDO open(const OutputLogUrl &url, const Log::LevelFlags flags)
    Q_UNUSED(url); Q_UNUSED(flags); return false;
}

bool FileLogOutput::write(const LogItem &item)
{
    Q_ASSERT("!MUSTDO"); // MUSTDO write(const LogItem &item)
    Q_UNUSED(item); return false;
}
