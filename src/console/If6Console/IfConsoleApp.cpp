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
    connect(this, &IfConsoleApp::initialized,
            this, &IfConsoleApp::start);
    QTimer::singleShot(500, this, &IfConsoleApp::initialize);
}

void IfConsoleApp::initialize()
{
    initializeLog();
    mpCache = new IfCache(this);
    mpCommandLine = new CommandLine(this);
    mpInputModule = new InputModule(this);
    mpOutputModule = new OutputModule(this);
    mWaiting.setFlag(WaitInputModule);
    connect(this, &IfConsoleApp::initialized,
            inputModule(), &InputModule::initialize);
    connect(inputModule(), &InputModule::initialized,
            this, &IfConsoleApp::setup);
    mWaiting.setFlag(WaitOutputModule);
    connect(this, &IfConsoleApp::initialized,
            outputModule(), &OutputModule::initialize);
    connect(outputModule(), &OutputModule::initialized,
            this, &IfConsoleApp::setup);

    emit initialized();
}

void IfConsoleApp::setup(VirtualIfModule *pModule)
{
    if (inputModule() == pModule)
        mWaiting.setFlag(WaitInputModule, false);
    else if (outputModule() == pModule)
        mWaiting.setFlag(WaitOutputModule, false);
    if (mWaiting)
        return;                                         /*====*/
    // command line
    // settings org/app/ini
}

void IfConsoleApp::start()
{
    LOG->start();
    inputMap() = settingsMap("Input");
    const QUrl cInputUrl = inputMap().value("URL").toUrl();
    LOG->INFO(QString("Input Url=%1").arg(cInputUrl.toString()));
    inputModule()->initialize();
    inputModule()->start(cInputUrl);
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

void IfConsoleApp::initializeLog()
{
    const QString cLogUrlsString = settings()->value("Output/LogUrls",
                                                     "file://./log/%-@.log;troll:").toString();
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

