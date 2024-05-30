#include "BaseIfModule.h"

#include "IfConsoleApp.h"

BaseIfModule::BaseIfModule(IfConsoleApp *parent)
    : QObject{parent}
    , mpApp(parent)
{
    setObjectName("BaseIfModule");
}
