#include "BaseExecutable.h"

#include <QCoreApplication>

#include "CommandLine.h"
#include "Log.h"
#include "Settings.h"

BaseExecutable::BaseExecutable(QObject *parent)
    : QObject{parent}
    , mpCommandLine(new CommandLine(this))
    , mpLog(new Log(this))
    , mpSettings(new Settings(this))
{
    setObjectName("BaseExecutable:CoreApplication");
}

bool BaseExecutable::isNull() const
{
    bool result = true;
    result &= ! isCore();
    // TODO gui & widget
    return result;
}

bool BaseExecutable::isCore() const
{
    return nullptr != mpCoreApp;
}

QString BaseExecutable::idString() const
{
    return QString("%1:%2:v%3")
        .arg(core()->organizationName(),
            core()->applicationName(),
            core()->applicationVersion());
}

void BaseExecutable::newCore(int argc, char **argv)
{
    QCoreApplication * result = nullptr;
    result = new QCoreApplication(argc, argv);
    Q_CHECK_PTR(result);
    if (mpCoreApp)
    {
        mpCoreApp->deleteLater();
        mpCoreApp = nullptr;
    }
    mpCoreApp = result;
}


