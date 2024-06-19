#include "VirtualIfModule.h"

#include "IfConsoleApp.h"

VirtualIfModule::VirtualIfModule(IfConsoleApp *parent)
    : QObject{parent}
    , mpApp(parent)
{
    setObjectName("BaseIfModule");
}
