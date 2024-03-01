#pragma once
#include"eIRexe.h"

#include <QObject>

#include <QFileInfo>
#include <QFileInfoList>
#include <QSettings>
#include <QString>
#include <QStringList>

class EIREXE_EXPORT CommandLine : public QObject
{
public: // ctors
    CommandLine(QObject * parent=nullptr);

public: // const
    QString orgName() const;
    QString appName() const;
    QSettings::SettingsMap settingsMap() const;

public slots:
    void process();

private:
    void handleSetting(const QString arg);
    void handleOrgApp(const QString arg);

private:
    QStringList mCurrentArguments;
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

inline QSettings::SettingsMap CommandLine::settingsMap() const
{
    return mSettingsMap;
}
