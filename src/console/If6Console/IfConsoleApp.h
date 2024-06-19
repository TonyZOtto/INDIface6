#pragma once

#include <QObject>

#include <QSettings>

#include <ConsoleApplication.h>
#include <IfCache.h>
class InputModule;

class IfConsoleApp : public ConsoleApplication
{
    Q_OBJECT
public:
    IfConsoleApp(int argc, char *argv[]);

public: // const
    QSettings::SettingsMap settingsMap();
    QSettings::SettingsMap settingsMap(const QString &groupKey);
    QSettings::SettingsMap settingsMap(const char * psz);

public: // non-const
    IfCache & cache();

public: // pointers
    QSettings * settings();
    InputModule * acquisition();
    QSettings::SettingsMap & inputMap();
    QSettings::SettingsMap & outputMap();

public slots:
    virtual void initialize();
    void start();

signals:
    void initialized();

private:
    IfCache mCache;
    QSettings * mpSettings=nullptr;
    InputModule * mpAcquisition=nullptr;
    QSettings::SettingsMap mInputMap;
    QSettings::SettingsMap mOutputMap;
};

inline IfCache &IfConsoleApp::cache() { return mCache; }
inline QSettings *IfConsoleApp::settings() { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline InputModule *IfConsoleApp::acquisition() { Q_CHECK_PTR(mpAcquisition); return mpAcquisition; }
inline QSettings::SettingsMap &IfConsoleApp::inputMap() { return mInputMap; }
inline QSettings::SettingsMap &IfConsoleApp::outputMap() { return mOutputMap; }
