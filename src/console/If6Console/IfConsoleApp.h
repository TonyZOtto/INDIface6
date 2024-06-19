#pragma once

#include <QCoreApplication>

#include <QFlags>
#include <QSettings>
#include <QVariant>


class CommandLine;
class IfCache;
class InputModule;
class OutputModule;
class VirtualIfModule;

class IfConsoleApp : public QCoreApplication
{
    Q_OBJECT
public:
    enum WaitingFlag
    {
        $null = 0,
        WaitInputModule,
        WaitOutputModule,
    };
    Q_DECLARE_FLAGS(WaitingFlags, WaitingFlag);

public:
    IfConsoleApp(int argc, char *argv[]);

public slots:
    void initialize();
    void setup(VirtualIfModule * pModule);
    void start();

signals:
    void initialized();
    void setuped();
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
    void initializeLog();

private:
    WaitingFlags mWaiting;
    IfCache * mpCache;
    CommandLine * mpCommandLine=nullptr;
    QSettings * mpSettings=nullptr;
    InputModule * mpInputModule=nullptr;
    OutputModule * mpOutputModule=nullptr;
    QSettings::SettingsMap mInputMap;
    QSettings::SettingsMap mOutputMap;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(IfConsoleApp::WaitingFlags);

inline IfCache *IfConsoleApp::cache() { return mpCache; }
inline QSettings *IfConsoleApp::settings() const { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline QSettings *IfConsoleApp::settings() { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline InputModule *IfConsoleApp::inputModule() { Q_CHECK_PTR(mpInputModule); return mpInputModule; }
inline OutputModule *IfConsoleApp::outputModule()  { Q_CHECK_PTR(mpOutputModule); return mpOutputModule; }
inline QSettings::SettingsMap &IfConsoleApp::inputMap() { return mInputMap; }
inline QSettings::SettingsMap &IfConsoleApp::outputMap() { return mOutputMap; }
