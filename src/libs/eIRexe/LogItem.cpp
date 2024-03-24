#include "LogItem.h"

#include "../eIRbase/Types.h"
#include "Context.h"
#include "LogMsgType.h"

Index LogItem::smNextSequence = 0;

LogItem::LogItem() {;}

LogItem::LogItem(const Context &ctx, const char *pchMessage)
    : mUid(true)
{
    flags().setFlag(Message);
    set(ctx);
    set(pchMessage);
}

LogItem::LogItem(const Context &ctx, const QString msg)
{
    flags().setFlag(Message);
    set(ctx);
    set(msg);
}

LogItem::LogItem(const Context &ctx, const char *pchFormat,
                 const char *argName1, const QVariant &argValue1,
                 const char *argName2, const QVariant &argValue2,
                 const char *argName3, const QVariant &argValue3,
                 const char *argName4, const QVariant &argValue4)
    : mUid(true)
{
    flags().setFlag(Format);
    set(ctx);
    ArgumentInfoList tAIL;
    tAIL << ArgumentInfo{argName1, argValue1, QString()};
    if (argValue2.isValid()) tAIL << ArgumentInfo{argName2, argValue2, QString()};
    if (argValue3.isValid()) tAIL << ArgumentInfo{argName3, argValue3, QString()};
    if (argValue4.isValid()) tAIL << ArgumentInfo{argName4, argValue4, QString()};
    set(pchFormat, tAIL);
}

LogItem::LogItem(const Context &ctx, const char *pchFormat,
                 const QVariant &argValue1, const QVariant &argValue2,
                 const QVariant &argValue3, const QVariant &argValue4)
    : mUid(true)
{
    flags().setFlag(Format);
    set(ctx);
    ArgumentInfoList tAIL;
    tAIL << ArgumentInfo{0, argValue1, QString()};
    if (argValue2.isValid()) tAIL << ArgumentInfo{0, argValue2, QString()};
    if (argValue3.isValid()) tAIL << ArgumentInfo{0, argValue3, QString()};
    if (argValue4.isValid()) tAIL << ArgumentInfo{0, argValue4, QString()};
    set(pchFormat, tAIL);
}

LogItem::LogItem(const Context &ctx, const char *pchFormat,
                 const QStringList &argNames, const QVariantList &argValues)
    : mUid(true)
{
    flags().setFlag(Format);
    set(ctx);
    ArgumentInfoList tAIL;
    const Count nArgs = qMin(argNames.count(), argValues.count());
    for (Index ix = 0; ix < Index(nArgs); ++ix)
        tAIL << ArgumentInfo{argNames[ix], argValues[ix], QString()};
    set(pchFormat, tAIL);
}

LogItem::LogItem(const Context &ctx, const LogCompareFlags lcf,
                 const char *expText, const QVariant &expValue,
                 const char *actText, const QVariant &actValue)
    : mUid(true)
{
    flags().setFlag(Expect);
    set(ctx);
    set(lcf);
    ArgumentInfoList tAIL;
    tAIL << ArgumentInfo{KeySeg(), expValue, QString(expText)};
    tAIL << ArgumentInfo{KeySeg(), actValue, QString(actText)};
    set(tAIL);
}

LogItem::LogItem(const Context &ctx, const LogCompareFlags lcf,
                 const char *assText, const QVariant &assValue)
    : mUid(true)
{
    flags().setFlag(Assert);
    set(ctx);
    set(lcf & Log::AssertMask);
    ArgumentInfoList tAIL;
    tAIL << ArgumentInfo{KeySeg(), assValue, QString(assText)};
    set(tAIL);
}

LogMsgType LogItem::msgtype() const
{
    return Log::msgType(m_level);
}

LogItem::Flags &LogItem::flags()
{
    return m_flags;
}

Index LogItem::setSequence()
{
    m_sequence = ++smNextSequence;
    return m_sequence;
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

void LogItem::set(const LogCompareFlags lcf)
{
    m_compareflags = lcf;
}

void LogItem::set(const char *pchMessage)
{
    m_message = QString(pchMessage);
}

void LogItem::set(const QString msg)
{
    m_message = msg;
}

void LogItem::set(const ArgumentInfoList &args)
{
    m_arguments = args;
}

void LogItem::set(const char *pchFormat, const ArgumentInfoList &args)
{
    m_format = QString(pchFormat),
    m_arguments = args;
}
