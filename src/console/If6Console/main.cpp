#include <QtDebug>

#include <eIRbase/VersionInfo.h>

#include "../../version.h"
#include "IfConsoleApp.h"
#include "version.h"

int main(int argc, char *argv[])
{
    IfConsoleApp a(argc, argv);
    VersionInfo vi(VER_MAJOR, VER_MINOR, VER_RELEASE, VER_BRANCH, VER_BUILD, VER_BRANCHNAME, VER_APPNAME, VER_ORGNAME);
    vi.setApp(a.core());
    qInfo() << a.idString();
    qInfo() << a.arguments();
    return a.core()->exec();
}
