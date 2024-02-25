#include <QtDebug>
#include <QCoreApplication>

#include <eIRbase/VersionInfo.h>
#include <eIRexe/ConsoleApplication.h>

#include "../../version.h"
#include "version.h"

int main(int argc, char *argv[])
{
    ConsoleApplication a(argc, argv);
    VersionInfo vi(VER_MAJOR, VER_MINOR, VER_RELEASE, VER_BRANCH, VER_BUILD, VER_BRANCHNAME, VER_APPNAME, VER_ORGNAME);
    vi.setApp(a.core());
    qInfo() << a.core()->organizationName() << a.core()->applicationName() << a.core()->applicationVersion();
    qInfo() << a.arguments();
    return a.core()->exec();
}
