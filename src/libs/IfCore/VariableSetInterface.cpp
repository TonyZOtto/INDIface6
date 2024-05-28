#include "VariableSetInterface.h"


#include <QtDebug>

#include "VariableKeyList.h"

VariableSetInterface::VariableSetInterface(QObject * parent)
    : QObject(parent)
    , VariableSet("VariableSetInterface")
    , _settings(new QSettings(parent))
{
    setObjectName("VariableSetInterface");
}

VariableSetInterface::VariableSetInterface(QSettings * settings,
                              const QString & group,
                              QObject * parent)
    : QObject(parent)
    , VariableSet(group.isEmpty() ? "VariableSetInterface" : group)
    , _settings(0)
{
    if (settings->fileName().isEmpty())
        _settings = new QSettings(settings->fileName(),
                                  settings->format(),
                                  parent);
    else
        _settings = new QSettings(settings->format(),
                                  settings->scope(),
                                  settings->organizationName(),
                                  settings->applicationName(),
                                  parent);

    _settings->beginGroup(group);
}

QString VariableSetInterface::orgName(void) const
{
    return _settings->organizationName();
}

QString VariableSetInterface::appName(void) const
{
    return _settings->applicationName();
}

QVariant VariableSetInterface::read(const QString & key,
                                    const QVariant & defaultValue)
{
    return _settings->value(key, defaultValue);
}

void VariableSetInterface::write(const QString & key,
                                 const QVariant & newValue)
{
    _settings->setValue(key, newValue);
}

void VariableSetInterface::read(void)
{
    foreach(QString key, _settings->allKeys())
        set(VariableKey(key), _settings->value(key));
}

void VariableSetInterface::write(void) const
{
    foreach (VariableKey vid, VariableSet::keys())
        _settings->setValue(vid, VariableSet::value(vid));
}

void VariableSetInterface::remove(const QString & key) const
{
    _settings->remove(key);
}

void VariableSetInterface::removeAll(void) const
{
    foreach(QString key, _settings->allKeys())
        _settings->remove(key);
}

void VariableSetInterface::update(void)
{

}
