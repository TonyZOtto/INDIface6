#pragma once
#include "eIRexe.h"

#include "BaseExecutable.h"

#include <QStringList>

class EIREXE_EXPORT ConsoleApplication : public BaseExecutable
{
public: // ctors
    explicit ConsoleApplication(int argc, char *argv[]);

public: // const
    QStringList arguments();

public: // non const

public: // pointers

private:
    QStringList mArguments;
};

inline QStringList ConsoleApplication::arguments()
{
    return mArguments;
}
