#include "ConsoleInitializer.h"

#include "IfConsoleApp.h"

ConsoleInitializer::ConsoleInitializer(IfConsoleApp *parent)
    : QObject{parent}
    , mpConsoleApp(parent)
{
    setObjectName("ConsoleInitializer");
}

void ConsoleInitializer::initBase()
{
    app()->initialize();
}
