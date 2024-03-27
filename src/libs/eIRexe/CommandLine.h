#pragma once
#include"eIRexe.h"

#include <QObject>

#include <QFileInfo>
#include <QFileInfoList>
#include <QSettings>
#include <QString>
#include <QStringList>
class BaseExecutable;

class EIREXE_EXPORT CommandLine : public QObject
{
public: // types
    enum SettingsType
    {
        $null = 0,
        AppOrg,
        IniFile,
        Arguments,
    };

public: // ctors
    CommandLine(QObject * parent=nullptr);

public: // const
    SettingsType settingsType() const;
    QString orgName() const;
    QString appName() const;
    QFileInfo iniFileInfo() const;
    QString iniFileName() const;
    QSettings::SettingsMap settingsMap() const;

public slots:
    void process(const QStringList &exeArgs);

private:
    void handleSetting(const QString arg);
    void handleOrgApp(const QString arg);

public:
    QStringList debugStrings() const;

private:
    QStringList mCurrentArguments;
    SettingsType mSettingsType=$null;
    QFileInfo mExeFileInfo;
    QFileInfo mIniFileInfo;
    QString mOrgName;
    QString mAppName;
    QSettings::SettingsMap mSettingsMap;
    QStringList mPositionalArguments;
    QFileInfoList mPositionalFileInfos;
};

inline QString CommandLine::orgName() const
{
    return mOrgName;
}

inline QString CommandLine::appName() const
{
    return mAppName;
}

inline QFileInfo CommandLine::iniFileInfo() const
{
    return mIniFileInfo;
}

inline QSettings::SettingsMap CommandLine::settingsMap() const
{
    return mSettingsMap;
}
