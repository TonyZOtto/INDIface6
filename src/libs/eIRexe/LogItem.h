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
    };
    Q_DECLARE_FLAGS(Flags, Flag);
    Q_FLAG(Flags);

    typedef Log::Level LogLevel;

    struct ArgumentInfo
    {
        KeySeg      name;
        QVariant    value;
        QString     info;
    };
    typedef QList<ArgumentInfo> ArgumentInfoList;

public: // ctors
    explicit LogItem();
    LogItem(const Context &ctx, const LogLevel lvl, const char * pchMessage);
    LogItem(const Context &ctx, const LogLevel lvl, const char * pchFormat,
            const char * argName1, const QVariant &argValue1,
            const char * argName2=0, const QVariant &argValue2=QVariant(),
            const char * argName3=0, const QVariant &argValue3=QVariant(),
            const char * argName4=0, const QVariant &argValue4=QVariant());
    LogItem(const Context &ctx, const LogLevel lvl, const char * pchFormat,
            const QStringList &argNames, const QVariantList &argValues);

private:
    void set(const Context &ctx);
    void set(const LogLevel lvl);
    void set(const char * pchMessage);
    void set(const char * pchFormat, const ArgumentInfoList &args);

private:
    Uid     mUid;


private: // ------------------------ properties ------------------------
    LogLevel            m_level;
    FunctionInfo        m_functionInfo;
    QQFileInfo          m_fileInfo;
    unsigned            m_fileLine;
    QString             m_message;
    QString             m_format;
    ArgumentInfoList    m_arguments;
    QString             m_debugHead;
    QString             m_debugFoot;
    QStringList         m_debugStrings;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(LogItem::Flags);
