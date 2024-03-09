//#include "Logger.h"

#include <QMetaEnum>
#include <QPartialOrdering>
#include <QVariant>

#include "../eIRbase/AText.h"
#include "../eIRcore/ObjectHelper.h"
#include "Log.h"
Q_GLOBAL_STATIC(Log, LOG);

Logger::Logger(QObject *parent)
    : QObject{parent}
{
    setObjectName("Logger");
}

bool Logger::open(const QUrl &url, const Log::Level maxLevel, const Log::Level minLevel)
{
    ObjectHelper tOH(LOG);
    const QMetaEnum cME = tOH.metaEnum("Level");
    const AText cFromName = cME.valueToKey(minLevel ? minLevel : Log::$minLevel);
    const AText cToName   = cME.valueToKey(maxLevel ? maxLevel : Log::$maxLevel);
    Log::LevelFlags flags = Log::LevelFlags(tOH.flagRange("Level", cFromName, cToName));
    return open(url, flags);
}

bool Logger::open(const QUrl &url, const Log::LevelFlags flags)
{

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
