#pragma once
#include"eIRexe.h"

#include <QObject>

class QCoreApplication;

class CommandLine;
class Log;
class Settings;

class EIREXE_EXPORT BaseExecutable : public QObject
{
    Q_OBJECT

protected: // ctors
    explicit BaseExecutable(QObject * parent=nullptr);

public: // const
    bool isNull() const;
    bool isCore() const;
    QString idString() const;

public: // pointers
    QCoreApplication *core() const;
    CommandLine *commandLine() const;
    Log *log() const;
    Settings *settings() const;

signals:

protected: // non-const
    void newCore(int argc, char **argv);

private:
    QCoreApplication * mpCoreApp=nullptr;
    CommandLine * mpCommandLine=nullptr;
    Log * mpLog=nullptr;
    Settings * mpSettings=nullptr;
};

inline QCoreApplication *BaseExecutable::core() const
{
    Q_CHECK_PTR(mpCoreApp); return mpCoreApp;
}

inline CommandLine *BaseExecutable::commandLine() const
{
    Q_CHECK_PTR(mpCommandLine); return mpCommandLine;
}

inline Log *BaseExecutable::log() const
{
    Q_CHECK_PTR(mpLog); return mpLog;
}

inline Settings *BaseExecutable::settings() const
{
    Q_CHECK_PTR(mpSettings); return mpSettings;
}


