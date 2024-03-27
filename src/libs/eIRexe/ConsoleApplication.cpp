#include "ConsoleApplication.h"

#include <QCoreApplication>
#include <QString>


ConsoleApplication::ConsoleApplication(int argc, char *argv[])
    : BaseExecutable(argc, argv)
{
    setObjectName("ConsoleApplication");
}

void ConsoleApplication::initialize()
{
    BaseExecutable::initialize();
}
