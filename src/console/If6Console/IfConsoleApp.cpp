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
    LOG->open(QUrl("troll:"), Log::UserFlags);
    const QUrl cLogFile = settings()->value("Output/LogDir").toUrl();
    const unsigned cLogFlags = settings()->value("Output/LogFlags",
                unsigned(Log::UserFlags | Log::TraceFlags)).toUInt();
    Q_ASSERT(LOG->open(QUrl("troll:"), Log::UserFlags));
    Q_ASSERT(LOG->open(cLogFile, Log::LevelFlags(cLogFlags)));
    emit initialized();
}

void IfConsoleApp::start()
{
    LOG->start();
    const QUrl cInputUrl = settings()->value("Input/URL").toUrl();
    LOG->INFO(QString("Input Url=%1").arg(cInputUrl.toString()));
}
