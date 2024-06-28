#include "IfConsoleApp.h"

#include <QString>
#include <QTimer>
#include <QUrl>

#include <CommandLine.h>
#include <IfCache.h>
#include <Log.h>
#include <Settings.h>

#include "InputModule.h"
#include "OutputModule.h"

IfConsoleApp::IfConsoleApp(int argc, char *argv[])
    : QCoreApplication{argc, argv}
{
    setObjectName("IfConsoleApp");
    QTimer::singleShot(500, this, &IfConsoleApp::initialize);
}

void IfConsoleApp::initialize()
{
    mpCache = new IfCache(this);
    mpCommandLine = new CommandLine(this);
    mpInputModule = new InputModule(this);
    mpOutputModule = new OutputModule(this);
    inputModule()->initialize();
    outputModule()->initialize();
    //PROGRESS("Initialization Complete");
    // TODO queue items before output open and logging started
    QTimer::singleShot(100, this, &IfConsoleApp::setup);
}

void IfConsoleApp::setup()
{
    // command line
    // settings org/app/ini
    mpSettings = new QSettings(QSettings::UserScope);
    settings()->setValue("Control/InitPath", QCoreApplication::applicationFilePath());
    settings()->setValue("Control/InitVer", QCoreApplication::applicationVersion());
    settings()->setValue("Control/InitTime", QDateTime::currentDateTime()
                                                 .toString("DyyyyMMdd-Thhmmsszzz"));
    startLog();
    PROGRESS("Initialization & Setup Complete");
    QTimer::singleShot(100, this, &IfConsoleApp::run);
}

void IfConsoleApp::run()
{
    PROGRESS("Start Running");
    connect(inputModule(), &InputModule::cachedFrame,
            outputModule(), &OutputModule::frameCached);
    inputModule()->run();
    outputModule()->run();
}

QVariant IfConsoleApp::get(const QString &aKey, const QVariant &aDephalt) const
{
    return settings()->value(aKey, aDephalt);
}

QSettings::SettingsMap IfConsoleApp::settingsMap() const
{
    QSettings::SettingsMap result;
    const QStringList tKeys = settings()->allKeys();
    foreach (const QString cSKey, tKeys)
    {
        const QVariant cVar = settings()->value(cSKey);
        result.insert(cSKey, cVar);
    }
    return result;
}

QSettings::SettingsMap IfConsoleApp::settingsMap(const QString &groupKey)
{
    settings()->beginGroup(groupKey);
    QSettings::SettingsMap result = settingsMap();
    settings()->endGroup();
    return result;
}

QSettings::SettingsMap IfConsoleApp::settingsMap(const char *psz)
{
    return settingsMap(QString(psz));
}

void IfConsoleApp::startLog()
{
    const QString cLogUrlsString
        = settings()->value("Output/LogUrls",
            "file:///./log/%-@.log;"
            "troll:///?Format=multitext").toString();
    LOG->close();
    if ("{none}" != cLogUrlsString)
    {
        LOG->open(cLogUrlsString);
        emit logOpened(cLogUrlsString);
    }

}

#if 0
Uid IfConsoleApp::addCache(const Key &key, const BaseImage &img)
{
    Q_UNUSED(key); Q_UNUSED(img);
    Q_ASSERT("!MUSTDO"); // MUSTDO
    return Uid();
}
#endif

