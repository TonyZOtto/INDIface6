#pragma once
#include"eIRexe.h"

#include <QCoreApplication>

class QFileInfo;

class CommandLine;
class Logger;
class Settings;

class EIREXE_EXPORT BaseExecutable : public QCoreApplication
{
    Q_OBJECT

protected: // ctors
    explicit BaseExecutable(int argc, char *argv[]);

public: // const
    QString idString() const;
    QStringList arguments() const;

public: // pointers
    CommandLine *commandLine() const;
    Logger *logger() const;
    Settings *settings() const;

public: // non-const

public slots:
    virtual void initialize();

signals:

protected: // non-const

protected: // non-const
    void newSettings(const QString &orgName, const QString & appName);
    void release();

private:
    CommandLine * mpCommandLine=nullptr;
    Logger * mpLog=nullptr;
    Settings * mpSettings=nullptr;
    QStringList mArguments;
};

inline CommandLine *BaseExecutable::commandLine() const
{
    Q_CHECK_PTR(mpCommandLine); return mpCommandLine;
}

inline Logger *BaseExecutable::logger() const
{
    Q_CHECK_PTR(mpLog); return mpLog;
}

inline Settings *BaseExecutable::settings() const
{
    Q_CHECK_PTR(mpSettings); return mpSettings;
}

inline QStringList BaseExecutable::arguments() const
{
    return mArguments;
}
