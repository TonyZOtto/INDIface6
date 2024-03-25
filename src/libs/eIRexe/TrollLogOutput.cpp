#include "TrollLogOutput.h"

#include "LogItem.h"
#include "LogMsgType.h"

TrollLogOutput::TrollLogOutput(QObject *parent)
    : BaseLogOutput{parent}
{}

bool TrollLogOutput::open(const OutputLogUrl &url, const Log::LevelFlags flags)
{
    // TODO TrollLogOutput::open() Anything?
    Q_UNUSED(url);
    mOpenMode = QIODevice::WriteOnly | QIODevice::Append;
    mFlags = flags;
    return true;
}

bool TrollLogOutput::write(const LogItem &item)
{
    static QString stFirstLine;
    const QStringList cLines = item.format(Log::TextFileMultiOutput).toStringList();
    if (stFirstLine != cLines.first())
    {
        write(item.msgtype(), cLines.first().toLocal8Bit());
        stFirstLine = cLines.first();
    }
    write(item.msgtype(), cLines.last().toLocal8Bit());
    return true;
}

void TrollLogOutput::write(const LogMsgType lmt, const char *pch)
{
    switch (lmt.type())
    {
    case LogMsgType::Info:      qInfo("%s", pch);       break;
    case LogMsgType::Debug:     qDebug("%s", pch);      break;
    case LogMsgType::Warning:   qWarning("%s", pch);    break;
    case LogMsgType::Error:     qCritical("%s", pch);   break;
    case LogMsgType::Fatal:     qFatal("%s", pch);      break;
    default:                    qDebug("%s", pch);      break;
    }
}
