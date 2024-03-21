#include "LogObject.h"

#include <QMetaEnum>

#include "../eIRcore/ObjectHelper.h"

Log::Log(QObject *parent) : QObject{parent} {;}

QtMsgType Log::msgtype(const Level lvl)
{

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
