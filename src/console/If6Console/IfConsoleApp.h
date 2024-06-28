#pragma once

#include <QCoreApplication>

#include <QFlags>
#include <QSettings>
#include <QVariant>

#include <eIRcore/MutexQueue.h>
#include <eirBase/Uid.h>

class CommandLine;
class IfCache;
class InputModule;
class OutputModule;
class VirtualIfModule;

class IfConsoleApp : public QCoreApplication
{
    Q_OBJECT
public:

public:
    IfConsoleApp(int argc, char *argv[]);

public slots:
    void initialize();
    void setup();
    void run();

signals:
    void logOpened(const QString aLogUrls);

public: // const
    QVariant get(const QString &aKey, const QVariant &aDephalt=QVariant()) const;
    QSettings::SettingsMap settingsMap() const;

public: // non-const
    QSettings::SettingsMap settingsMap(const QString &groupKey);
    QSettings::SettingsMap settingsMap(const char * psz);
    void set(const QString &aKey, const QVariant &aValue);
    IfCache * cache();

public: // pointers
    QSettings * settings() const;
    QSettings * settings();
    InputModule * inputModule();
    OutputModule * outputModule();
    QSettings::SettingsMap & inputMap();
    QSettings::SettingsMap & outputMap();

private slots:
    void startLog();

private:
    IfCache * mpCache;
    MutexQueue<Uid> mInputQueue;
    CommandLine * mpCommandLine=nullptr;
    QSettings * mpSettings=nullptr;
    InputModule * mpInputModule=nullptr;
    OutputModule * mpOutputModule=nullptr;
    QSettings::SettingsMap mInputMap;
    QSettings::SettingsMap mOutputMap;
};

inline IfCache *IfConsoleApp::cache() { return mpCache; }
inline QSettings *IfConsoleApp::settings() const { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline QSettings *IfConsoleApp::settings() { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline InputModule *IfConsoleApp::inputModule() { Q_CHECK_PTR(mpInputModule); return mpInputModule; }
inline OutputModule *IfConsoleApp::outputModule()  { Q_CHECK_PTR(mpOutputModule); return mpOutputModule; }
inline QSettings::SettingsMap &IfConsoleApp::inputMap() { return mInputMap; }
inline QSettings::SettingsMap &IfConsoleApp::outputMap() { return mOutputMap; }
