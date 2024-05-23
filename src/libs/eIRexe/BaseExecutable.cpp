#include "BaseExecutable.h"

#include <QCoreApplication>
#include <QFileInfo>

#include "../eIRbase/Types.h"
#include "CommandLine.h"
#include "Logger.h"
#include "Settings.h"

BaseExecutable::BaseExecutable(int argc, char *argv[])
    : QCoreApplication{argc, argv}
    , mpCommandLine(new CommandLine(this))
    , mpLog(new Logger(this))
    , mpSettings(new Settings(this))
{
    setObjectName("BaseExecutable");
    /* Alleged Windows bug, so we build our own */
    for (Index ix = 0; ix < argc; ++ix) mArguments << QString(argv[ix]);
    qInfo() << argc << *argv << mArguments;
}

QString BaseExecutable::idString() const
{
    return QString("%1:%2:v%3").arg(organizationName(),
            applicationName(), applicationVersion());
}

void BaseExecutable::initialize()
{
    commandLine()->process(arguments());
    qInfo() << Q_FUNC_INFO << commandLine()->debugStrings();
    if ( ! commandLine()->newSettingsSpecNull())
    {
        if (commandLine()->iniFileName().isEmpty())
        {
            newSettings(commandLine()->orgName(), commandLine()->appName());
        }
        else
        {
            newSettings(QFileInfo(commandLine()->iniFileName()));
        }
    }
    settings()->insert(commandLine()->settingsMap());
    qInfo() << Q_FUNC_INFO << settings()->debugStrings();
}

void BaseExecutable::newSettings(const QString &orgName, const QString &appName)
{
    releaseSettings();
    mpSettings = new Settings(orgName, appName, this);
}

void BaseExecutable::newSettings(const QFileInfo &fi)
{
    releaseSettings();
    mpSettings = new Settings(fi.filePath(), this);
}

void BaseExecutable::releaseSettings()
{
    if (mpSettings)
    {
        mpSettings->deleteLater();
        mpSettings = nullptr;
    }
}


