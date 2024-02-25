#include "BaseExecutable.h"

#include <QCoreApplication>

BaseExecutable::BaseExecutable(QObject *parent)
    : QObject{parent}
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


