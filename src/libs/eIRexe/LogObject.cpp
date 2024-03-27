#include "LogObject.h"

#include <QMetaEnum>

#include "../eIRcore/ObjectHelper.h"
#include "LogMsgType.h"

Log::Log(QObject *parent) : QObject{parent} {;}

// ======================= static ====================

EIREXE_EXPORT Log::LevelFlags Log::UserFlags = Log::LevelFlags(Log::FlagPrefer | Log::FlagDetail |
                                              Log::FlagDump | Log::FlagInfo |
                                              Log::FlagProgress | Log::FlagInfo |
                                              Log::FlagAssert | Log::FlagError |
                                              Log::FlagFatal);
EIREXE_EXPORT Log::LevelFlags Log::TraceFlags = Log::LevelFlags(Log::FlagTFnArg | Log::FlagTFnLeave |
                                         Log::FlagTFnEnter | Log::FlagTDetail |
                                         Log::FlagTDump | Log::FlagTrace |
                                         Log::FlagTPrefer | Log::FlagExpect |
                                         Log::FlagTWarning | Log::FlagTProgress |
                                         Log::FlagTExpect | Log::FlagTError |
                                         Log::FlagTFatal);

LogMsgType Log::msgType(const Log::Level lvl)
{
    LogMsgType result = LogMsgType::$null;
    switch (lvl)
    {
    case Prefer:    case Detail:    case Dump:
    case Info:      case Progress:
        result = LogMsgType::Info;          break;
    case TFnArg:    case TFnLeave:  case TFnEnter:
    case TDetail:   case TDump:     case Trace:
    case TPrefer:   case TInfo:     case TProgress:
        result = LogMsgType::Debug;         break;
    case Warning:   case TWarning:
        result = LogMsgType::Warning;       break;
    case Error:     case TError:
    case Expect:    case TExpect:
        result = LogMsgType::Error;         break;
    case Fatal:     case TFatal:
        result = LogMsgType::Fatal;         break;
    default:
        /* leave $null result */            break;
    }

    return result;
}

QChar Log::levelChar(const Level lvl)
{
    QChar result('?');
    Q_UNUSED(lvl); // TODO Log::levelChar()
    return result;
}

Log::OutputScheme Log::outputScheme(const AText key)
{
    Log::OutputScheme result = Log::$nullOutputScheme;
    ObjectHelper tOH(new Log);
    const QMetaEnum cME = tOH.metaEnum("OutputScheme");
    const int cScheme = cME.keyToValue(key);
    if (cScheme > 0) result = Log::OutputScheme(cScheme);
    return result;
}
