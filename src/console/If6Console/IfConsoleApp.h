#pragma once

#include <QObject>

#include <QSettings>

#include <ConsoleApplication.h>
#include <IfCache.h>
class ImageAcquisition;

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
    ImageAcquisition * acquisition();
    QSettings::SettingsMap & inputMap();

public slots:
    virtual void initialize();
    void start();

signals:
    void initialized();

private:
    IfCache mCache;
    QSettings * mpSettings=nullptr;
    ImageAcquisition * mpAcquisition=nullptr;
    QSettings::SettingsMap mInputMap;
};

inline IfCache &IfConsoleApp::cache() { return mCache; }
inline QSettings *IfConsoleApp::settings() { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline ImageAcquisition *IfConsoleApp::acquisition() { Q_CHECK_PTR(mpAcquisition); return mpAcquisition; }
inline QSettings::SettingsMap &IfConsoleApp::inputMap() { return mInputMap; }
