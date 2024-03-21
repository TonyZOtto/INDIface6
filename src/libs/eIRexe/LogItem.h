#pragma once
#include "eIRexe.h"

#include <QObject>

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantList>

#include "../eIRcore/QQFileInfo.h"
#include "../eIRbase/KeySeg.h"
#include "../eIRbase/Uid.h"
#include "Context.h"
#include "FunctionInfo.h"
#include "LogObject.h"

class EIREXE_EXPORT LogItem : public QObject
{
    Q_GADGET
public: // types
    enum Flag
    {
        $null = 0,
        Message         = 0x00000001,
        Format          = 0x00000002,
        Expect          = 0x00000004,
        Assert          = 0x00000008,
    };
    Q_DECLARE_FLAGS(Flags, Flag);
    Q_FLAG(Flags);

    typedef Log::Level          LogLevel;
    typedef Log::Compare        LogCompare;
    typedef Log::CompareFlags   LogCompareFlags;
    typedef LogItem::Flags      LogItemFlags;

    struct ArgumentInfo
    {
        KeySeg      name;
        QVariant    value;
        QString     text;
    };
    typedef QList<ArgumentInfo> ArgumentInfoList;

public: // ctors
    explicit LogItem();
    LogItem(const Context &ctx, const char * pchMessage);
    LogItem(const Context &ctx, const char * pchFormat,
            const char * argName1, const QVariant &argValue1,
            const char * argName2=0, const QVariant &argValue2=QVariant(),
            const char * argName3=0, const QVariant &argValue3=QVariant(),
            const char * argName4=0, const QVariant &argValue4=QVariant());
    LogItem(const Context &ctx, const char * pchFormat,
            const QVariant &argValue1, const QVariant &argValue2=QVariant(),
            const QVariant &argValue3=QVariant(), const QVariant &argValue4=QVariant());
    LogItem(const Context &ctx, const char * pchFormat,
            const QStringList &argNames, const QVariantList &argValues);
    LogItem(const Context &ctx, const LogCompareFlags lcf,
            const char * expText, const QVariant &expValue,
            const char * actText, const QVariant &actValue);
    LogItem(const Context &ctx, const LogCompareFlags lcf,
            const char * assText, const QVariant &assValue);

private:
    Flags & flags();
    Index setSequence();
    void set(const Context &ctx);
    void set(const LogLevel lvl);
    void set(const LogCompareFlags lcf);
    void set(const char * pchMessage);
    void set(const ArgumentInfoList &args);
    void set(const char * pchFormat, const ArgumentInfoList &args);

private:
    Uid     mUid;
    static Index smNextSequence;

private: // ------------------------ properties ------------------------
    LogLevel            m_level;
    Flags               m_flags;
    Index               m_sequence;
    FunctionInfo        m_functionInfo;
    QQFileInfo          m_fileInfo;
    unsigned            m_fileLine;
    QString             m_message;
    QString             m_format;
    LogCompareFlags     m_compareflags;
    ArgumentInfoList    m_arguments;
    QString             m_debugHead;
    QString             m_debugFoot;
    QStringList         m_debugStrings;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(LogItem::Flags);
