#include "OutputModule.h"

OutputModule::OutputModule(IfConsoleApp *parent)
    : VirtualIfModule(parent)
{
    setObjectName("OutputModule");
}

void OutputModule::initialize()
{

}

void OutputModule::run()
{

}

void OutputModule::frameCached(const Uid aUid)
{
    qInfo() << Q_FUNC_INFO << aUid.tail();
}
