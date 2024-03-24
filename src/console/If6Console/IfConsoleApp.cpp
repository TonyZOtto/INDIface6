#include "IfConsoleApp.h"

IfConsoleApp::IfConsoleApp(int argc, char *argv[])
    : ConsoleApplication{argc, argv}
{
    setObjectName("IfConsoleApp");
}

void IfConsoleApp::initialize()
{
    ConsoleApplication::initialize();
}
