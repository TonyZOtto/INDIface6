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

KeyMap IfConsoleApp::settingsMap(const Key &groupKey)
{
    KeyMap result;
    const QString cPrefix = groupKey();
    if (groupKey.notNull()) settings()->beginGroup(cPrefix);
    const QStringList tKeys = settings()->allKeys();
    foreach (const QString cSKey, tKeys)
    {
        const Key cKey(cSKey);
        const QVariant cVar = settings()->value(cSKey);
        result.insert(cKey, cVar);
    }
    if ( ! cPrefix.isEmpty()) settings()->endGroup();
    return result;
}

KeyMap IfConsoleApp::settingsMap(const char *psz)
{
    return settingsMap(Key(psz));
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
    //const QUrl cLogUrl = settings()->value("Output/LogUrl", "file://./log/%-@.log").toUrl();
//    const Log::LevelFlags cLogFlags = Log::LevelFlags(settings()->value("Output/LogFlags",
  //                                      unsigned(Log::UserFlags | Log::TraceFlags)).toUInt());
    //Q_ASSERT(LOG->open(QUrl("troll:"), cLogFlags));
    //Q_ASSERT(LOG->open(cLogUrl, cLogFlags));
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
