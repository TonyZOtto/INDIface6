#pragma once

#include <QObject>

class QSettings;

#include <ConsoleApplication.h>
#include <IfCache.h>
class ImageAcquisition;

class IfConsoleApp : public ConsoleApplication
{
    Q_OBJECT
public:
    IfConsoleApp(int argc, char *argv[]);

public: // const
    KeyMap settingsMap(const Key &groupKey=Key());
    KeyMap settingsMap(const char * psz);

public: // non-const
    IfCache & cache();
//    Uid addCache(const Key &key, const BaseImage &img);

public: // pointers
    QSettings * settings();
    ImageAcquisition * acquisition();
    KeyMap & inputMap();

public slots:
    virtual void initialize();
    void start();

signals:
    void initialized();

private:
    IfCache mCache;
    QSettings * mpSettings=nullptr;
    ImageAcquisition * mpAcquisition=nullptr;
    KeyMap mInputMap;
};

inline IfCache &IfConsoleApp::cache() { return mCache; }
inline QSettings *IfConsoleApp::settings() { Q_CHECK_PTR(mpSettings); return mpSettings; }
inline ImageAcquisition *IfConsoleApp::acquisition() { Q_CHECK_PTR(mpAcquisition); return mpAcquisition; }
inline KeyMap &IfConsoleApp::inputMap() { return mInputMap; }
