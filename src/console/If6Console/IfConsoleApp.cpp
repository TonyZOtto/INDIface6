#include "IfConsoleApp.h"

#include <QString>
#include <QTimer>
#include <QUrl>

#include <Log.h>
#include <Settings.h>

IfConsoleApp::IfConsoleApp(int argc, char *argv[])
    : ConsoleApplication{argc, argv}
{
    setObjectName("IfConsoleApp");
    connect(this, &IfConsoleApp::initialized,
            this, &IfConsoleApp::start);
    QTimer::singleShot(500, this, &IfConsoleApp::initialize);
}

void IfConsoleApp::initialize()
{
    ConsoleApplication::initialize();
    //const QUrl cLogUrl = settings()->value("Output/LogUrl", "file://./log/%-@.log").toUrl();
    const Log::LevelFlags cLogFlags = Log::LevelFlags(settings()->value("Output/LogFlags",
                                        unsigned(Log::UserFlags | Log::TraceFlags)).toUInt());
    Q_ASSERT(LOG->open(QUrl("troll:"), cLogFlags));
    //Q_ASSERT(LOG->open(cLogUrl, cLogFlags));
    emit initialized();
}

void IfConsoleApp::start()
{
    LOG->start();
    const QUrl cInputUrl = settings()->value("Input/URL").toUrl();
    LOG->INFO(QString("Input Url=%1").arg(cInputUrl.toString()));
}
