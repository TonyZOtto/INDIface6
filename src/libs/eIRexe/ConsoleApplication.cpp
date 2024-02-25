#include "ConsoleApplication.h"

#include <QString>

ConsoleApplication::ConsoleApplication(int argc, char *argv[])
{
    setObjectName("ConsoleApplication");
    newCore(argc, argv);
    while (argc--)
        mArguments << QString(*argv++);
}
