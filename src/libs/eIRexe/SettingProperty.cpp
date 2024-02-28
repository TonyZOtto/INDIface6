#include "SettingProperty.h"

#include "Settings.h"


SettingProperty::SettingProperty(Settings * Settings,
                                 QObject * Object,
                                 const QString & Key,
                                 const QString & PropertyName,
                                 Settings::Flags f)
    : QObject(Settings)
    , settings(Settings)
    , object(Object)
    , key(Key)
    , propertyName(PropertyName)
    , mFlags(f)
{
    QObject::connect(Object, SIGNAL(destroyed(QObject*)),
                     Settings, SLOT(objectDestroyed(QObject*)));
}

void SettingProperty::setValue(const QVariant & newValue)
{
    if (object->property(qPrintable(propertyName)) != newValue)
    {
        object->setProperty(qPrintable(propertyName), newValue);
        mFlags |= Settings::Dirty | Settings::Changed;
        mValue = newValue;
        settings->emitPropertyChanged(key);
    }
}
