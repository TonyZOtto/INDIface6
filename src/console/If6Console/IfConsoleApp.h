#pragma once

#include <QObject>
#include <ConsoleApplication.h>

class IfConsoleApp : public ConsoleApplication
{
    Q_OBJECT
public:
    IfConsoleApp(int argc, char *argv[]);
};
