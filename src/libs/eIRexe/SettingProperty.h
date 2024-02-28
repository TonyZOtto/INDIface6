#pragma once
#include"eIRexe.h"

#include <QObject>

#include <QVariant>

#include "Settings.h"

class EIREXE_EXPORT SettingProperty : public QObject
{
    Q_OBJECT
public:
    SettingProperty(Settings * Settings,
                    QObject * Object,
                    const QString & Key,
                    const QString & PropertyName,
                    Settings::Flags f=Settings::$null);
    QVariant value() const;
    void setValue(const QVariant & newValue);

    //	private:
public:
    Settings *	settings;
    QObject * object;
    QString key;
    QString propertyName;
    QVariant mValue;
    Settings::Flags mFlags;

signals:
};

inline QVariant SettingProperty::value() const
{
    return mValue;
}
