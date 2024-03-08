#include "LogItem.h"

#include "../eIRbase/Types.h"

LogItem::LogItem() {;}

LogItem::LogItem(const Context &ctx, const LogLevel lvl, const char *pchMessage)
    : mUid(true)
{
    set(ctx);
    set(lvl);
    set(pchMessage);
}

LogItem::LogItem(const Context &ctx, const LogLevel lvl, const char *pchFormat,
                 const char *argName1, const QVariant &argValue1,
                 const char *argName2, const QVariant &argValue2,
                 const char *argName3, const QVariant &argValue3,
                 const char *argName4, const QVariant &argValue4)
    : mUid(true)
{
    set(ctx);
    set(lvl);
    ArgumentInfoList tAIL;
    tAIL << ArgumentInfo{argName1, argValue1, QString()};
    if (argValue2.isValid()) tAIL << ArgumentInfo{argName2, argValue2, QString()};
    if (argValue3.isValid()) tAIL << ArgumentInfo{argName3, argValue3, QString()};
    if (argValue4.isValid()) tAIL << ArgumentInfo{argName4, argValue4, QString()};
    set(pchFormat, tAIL);
}

LogItem::LogItem(const Context &ctx, const LogLevel lvl, const char *pchFormat,
                 const QStringList &argNames, const QVariantList &argValues)
    : mUid(true)
{
    set(ctx);
    set(lvl);
    ArgumentInfoList tAIL;
    const Count nArgs = qMin(argNames.count(), argValues.count());
    for (Index ix = 0; ix < Index(nArgs); ++ix)
        tAIL << ArgumentInfo{argNames[ix], argValues[ix], QString()};
    set(pchFormat, tAIL);
}

void LogItem::set(const Context &ctx)
{
    m_functionInfo.set(ctx.functionInfo()),
    m_fileInfo.set(ctx.fileInfo()),
    m_fileLine = ctx.fileLine();
}

void LogItem::set(const LogLevel lvl)
{
    m_level = lvl;
}

void LogItem::set(const char *pchMessage)
{
    m_message = QString(pchMessage);
}

void LogItem::set(const char *pchFormat, const ArgumentInfoList &args)
{
    m_format = QString(pchFormat),
    m_arguments = args;
}
