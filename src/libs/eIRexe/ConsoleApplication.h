#pragma once
#include "eIRexe.h"

#include "BaseExecutable.h"

#include <QStringList>

class EIREXE_EXPORT ConsoleApplication : public BaseExecutable
{
    Q_OBJECT

public: // ctors
    explicit ConsoleApplication(int argc, char *argv[]);

public: // const

public: // non const
public: // non-const

public slots:
    virtual void initialize();


public: // pointers

private:
};

