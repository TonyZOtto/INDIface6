#include "IfConsoleApp.h"

#include <QString>
#include <QTimer>
#include <QUrl>

#include <Log.h>
#include <Settings.h>

#include "ImageAcquisition.h"

IfConsoleApp::IfConsoleApp(int argc, char *argv[])
    : ConsoleApplication{argc, argv}
    , mCache(this)
{
    setObjectName("IfConsoleApp");
    connect(this, &IfConsoleApp::initialized,
            this, &IfConsoleApp::start);
    QTimer::singleShot(500, this, &IfConsoleApp::initialize);
}

QSettings::SettingsMap IfConsoleApp::settingsMap()
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

#if 0
Uid IfConsoleApp::addCache(const Key &key, const BaseImage &img)
{
    Q_UNUSED(key); Q_UNUSED(img);
    Q_ASSERT("!MUSTDO"); // MUSTDO
    return Uid();
}
#endif

void IfConsoleApp::initialize()
{
    ConsoleApplication::initialize();
    const QString cLogUrlsString = settings()->value("Output/LogUrls",
                            "file://./log/%-@.log;troll:").toString();
    LOG->closeAll();
    if ("{none}" != cLogUrlsString)
        LOG->open(cLogUrlsString);
    mpAcquisition = new ImageAcquisition(this);
    emit initialized();
}

void IfConsoleApp::start()
{
    LOG->start();
    inputMap() = settingsMap("Input");
    const QUrl cInputUrl = inputMap().value("URL").toUrl();
    LOG->INFO(QString("Input Url=%1").arg(cInputUrl.toString()));
    acquisition()->initialize();
    acquisition()->start(cInputUrl);
}
