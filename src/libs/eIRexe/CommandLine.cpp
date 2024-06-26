#include "CommandLine.h"

#include <QCoreApplication>
#include <QString>
#include <QVariant>

#include "BaseExecutable.h"
#include "Log.h"
#include "../eIRbase/Types.h"

CommandLine::CommandLine(QObject *parent)
    : QObject(parent)
{
    setObjectName("CommandLine");
}

CommandLine::SettingsType CommandLine::settingsType() const
{
    CommandLine::SettingsType result = mSettingsType;
    if ($null == result && ! mSettingsMap.isEmpty())
        result = Arguments;
    return result;
}

void CommandLine::process(const QStringList &exeArgs)
{
    mExeArguments = exeArgs;
    mExeFileInfo = QFileInfo(mExeArguments.takeFirst());
    foreach (const QString tArgString, mExeArguments)
    {
        const int tFirstChar = tArgString.first(1).data()->cell();
        const QString tArgument = tArgString.mid(1);
        switch (tFirstChar)
        {
        case '/':   handleSetting(tArgument);                   break;
        case '%':   handleOrgApp(tArgument);                    break;
        default:    mPositionalArguments.append(tArgString);
            mPositionalFileInfos.append(QFileInfo(tArgString));  break;
        }
    }
}

void CommandLine::handleSetting(const QString arg)
{
    const Index cEqualsIndex = arg.indexOf('=');
    QString tKey;
    QVariant tValue;
    if (cEqualsIndex < 0)
    {
        tKey = arg;
        if (tKey.endsWith('!'))
        {
            tKey.chop(1);
            tValue = QVariant(false);
        }
        else
        {
            tValue = QVariant(true);
        }
    }
    else if (cEqualsIndex > 0)
    {
        tKey = arg.left(cEqualsIndex);
        tValue = QVariant(arg.mid(cEqualsIndex + 1));
    }
//  else =0, ignore '/=xxx' argument
    mSettingsMap.insert(tKey, tValue);
}

void CommandLine::handleOrgApp(const QString arg)
{
    QString tOrg = QCoreApplication::organizationName();
    QString tApp = QCoreApplication::applicationName();
    const Index cSlashIndex = arg.indexOf('/');
    if (cSlashIndex <= 0) // no / = all App
    {
        tApp = arg;
    }
    else if (arg.endsWith('/')) // = all Org  (cSlashIndex >= arg.count())
    {
        tOrg = arg.chopped(1);
    }
    else if (cSlashIndex > 0)
    {
        tOrg = arg.left(cSlashIndex - 1);
        tApp = arg.mid(cSlashIndex + 1);
    }
    mOrgName = tOrg, mAppName = tApp;
}

QStringList CommandLine::debugStrings() const
{
    QStringList result;
    result << "ExeArguments=" + mExeArguments.join(';');
    result << "ExeFileInfo=" + mExeFileInfo.filePath();
    result << "Org/App=" + mOrgName + "/" + mAppName;
    foreach (const QString cKey, mSettingsMap.keys())
        result << cKey + "=" + mSettingsMap[cKey].toString();
    result << "PositionalArguments=" + mPositionalArguments.join(';');

    return result;
}

