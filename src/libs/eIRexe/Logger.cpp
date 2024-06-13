//#include "Logger.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QPartialOrdering>
#include <QString>
#include <QVariant>

#include "../eIRbase/AText.h"
#include "../eIRcore/ObjectHelper.h"
#include "Log.h"
#include "LogMacros.h"
#include "OutputLogUrlList.h"
#include "TrollLogOutput.h"

Logger::Logger(QObject *parent)
    : QObject{parent}
{
    setObjectName("Logger");
}

bool Logger::open(const QString &aOutputLogUrlStrings)
{
    const OutputLogUrlList cOutputLogUrlList(aOutputLogUrlStrings);
    Q_ASSERT(!"MUSTDO"); return false; // MUSTDO
}

bool Logger::start()
{
    const QString cStartString = QString("Starting %1 v%2 from %3 on PID %4 at %5")
                                     .arg(QCoreApplication::applicationName())
                                     .arg(QCoreApplication::applicationVersion())
                                     .arg(QCoreApplication::applicationDirPath())
                                     .arg(QCoreApplication::applicationPid())
                                     .arg(QDateTime::currentDateTime()
                                              .toString("yyyy-MM-dd hh:mm"));
    LogItem tLI(LOGCTX(Log::Progress), cStartString);
    LOG->add(tLI);
    return true;
}
/*
 #include <QApplication>
 #include <stdio.h>
 #include <stdlib.h>

 QtMessageHandler originalHandler = nullptr;

 void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
 {
     QString message = qFormatLogMessage(type, context, msg);
     static FILE *f = fopen("log.txt", "a");
     fprintf(f, "%s\n", qPrintable(message));
     fflush(f);

     if (originalHandler)
         *originalHandler(type, context, msg);
 }

 int main(int argc, char **argv)
 {
     originalHandler = qInstallMessageHandler(logToFile);
     QApplication app(argc, argv);
     ...
     return app.exec();
 }
*/

#if 0
bool Logger::open(const OutputLogUrl &url, const Log::Level maxLevel, const Log::Level minLevel)
{
    ObjectHelper tOH(LOG);
    const QMetaEnum cME = tOH.metaEnum("Level");
    const AText cFromName = cME.valueToKey(minLevel ? minLevel : Log::$minLevel);
    const AText cToName   = cME.valueToKey(maxLevel ? maxLevel : Log::$maxLevel);
    Log::LevelFlags flags = Log::LevelFlags(tOH.flagRange("Level", cFromName, cToName));
    return open(url, flags);
}
bool Logger::open(const OutputLogUrl &url, const Log::LevelFlags flags)
{
    bool result = false;
    return result;
}
#endif

void Logger::add(const LogItem &aLogItem)
{
    mInputItemQueue.enqueue(aLogItem);
    emit queued(aLogItem);
    emit queueCount(mInputItemQueue.count());
}

bool Logger::open(const OutputLogUrl &aOutputLogUrl)
{
    bool result = false;
    const QString cUrlScheme = aOutputLogUrl.scheme();
    const Log::OutputScheme cOutScheme = Log::outputScheme(cUrlScheme);
    switch (cOutScheme)
    {
    case Log::FileOutputScheme:     result = openFile(aOutputLogUrl);      break;
    case Log::TrollOutputScheme:    result = openTroll(aOutputLogUrl);     break;
    case Log::SqlOutputScheme:      result = openSql(aOutputLogUrl);       break;
    default:                        /* false result */                  break;
    };

    if (result)     mMasterOutputLevelFlags |= aOutputLogUrl.levelFlags();
    return result;
}

bool Logger::openFile(const OutputLogUrl &aOutputLogUrl)
{
    Q_UNUSED(aOutputLogUrl); return true; // MUSTDO
    QString tFileName = aOutputLogUrl.toLocalFile();
    // TODO replace % with Org-App
    // TODO replace @ with timestamp
}

bool Logger::openTroll(const OutputLogUrl &aOutputLogUrl)
{
    bool result = false;
    TrollLogOutput * pOut = new TrollLogOutput(aOutputLogUrl, this);
    Q_CHECK_PTR(pOut);
    result = pOut->open(aOutputLogUrl);
    pOut->mode(result ? QIODevice::WriteOnly : QIODevice::NotOpen);
    return result;
}

bool Logger::openSql(const OutputLogUrl &aOutputLogUrl)
{
    Q_UNUSED(aOutputLogUrl); return false;// MUSTDO
}

Boolean Logger::compare(const Log::Compare c, const QVariant &expected, const QVariant &actual)
{
    Boolean result; // isNull()
    QVariant tExp = expected, tAct = actual;
    const QPartialOrdering tQPO = QVariant::compare(tExp, tAct);
    if (tQPO == QPartialOrdering::Unordered)
        result.invalidate();
    else
        result = compare(c, tQPO);
    return result;
}

Boolean Logger::compare(const Log::Compare c, const QPartialOrdering qpo)
{
    Boolean result; // isNull()
    if (QPartialOrdering::Unordered == qpo)     result.invalidate();
    else switch(c)
        {
        case Log::Equals:           result.set(equal(qpo));                         break;
        case Log::NotEqual:         result.set( ! equal(qpo));                      break;
        case Log::GreaterThan:      result.set(greater(qpo));                       break;
        case Log::LessThan:         result.set( ! greater(qpo));                    break;
        case Log::GreaterEqual:     result.set(equal(qpo) || greater(qpo));         break;
        case Log::LessEqual:        result.set(equal(qpo) || ( ! greater(qpo)));    break;
        default:                    Q_ASSERT(!"Can't get here");                    break;
        }
    return result;
}

bool Logger::equal(const QPartialOrdering qpo)
{
    return QPartialOrdering::Equivalent == qpo;
}

bool Logger::greater(const QPartialOrdering qpo)
{
    return QPartialOrdering::Greater == qpo;
}
