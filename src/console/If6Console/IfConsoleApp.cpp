#include "IfConsoleApp.h"

#include <QTimer>

#include <Log.h>

IfConsoleApp::IfConsoleApp(int argc, char *argv[])
    : ConsoleApplication{argc, argv}
{
    setObjectName("IfConsoleApp");
    QTimer::singleShot(500, this, &IfConsoleApp::initialize);
}

void IfConsoleApp::initialize()
{
    ConsoleApplication::initialize();
    LOG->open(QUrl("troll:"), Log::UserFlags);
}
