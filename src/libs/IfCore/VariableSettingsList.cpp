#include "VariableSettingsList.h"

#include <QtCore/QTimer>
#include <QtCore/QVariant>

#include "VariableKeyList.h"

VariableSettingsList::VariableSettingsList(QObject * parent)
    : QObject(parent)
    , mpDefault(new VariableSettings(this))
    , mUpdateMsec(0)
    , mIsUpdateRead(false)
    , mpWatchTimer(0)
{
    mpDefault->setName("default");
    mSettingsList.append(mpDefault);
}

VariableSettingsList::~VariableSettingsList()
{
    stop();
}

void VariableSettingsList::add(VariableSettings * vsi)
{
    mSettingsList.prepend(vsi);
}

void VariableSettingsList::add(QString string)
{
    VariableSettings * vsi = new VariableSettings(string, this);
    if (QSettings::NoError == vsi->status())
    {
        vsi->setName(string);
        vsi->read();
        if ( ! vsi->isEmpty())
            mSettingsList.prepend(vsi);
        else
            delete vsi;
    }
}

void VariableSettingsList::addTrigger(const VariableKey & key)
{
    mTriggerSet.insert(key);
    set(key, QString());
}

bool VariableSettingsList::isTrigger(const VariableKey &key)
{
    return mTriggerSet.contains(key);
}

void VariableSettingsList::setUpdateMsec(const int msec)
{
    mUpdateMsec = msec;
    // if started, restart
    if (mpWatchTimer) start();
}

void VariableSettingsList::setUpdateRead(const bool readOnUpdate)
{
    mIsUpdateRead = readOnUpdate;
}

bool VariableSettingsList::contains(const VariableKey & key) const
{
    (void)key;
    return false;
}

VariableSettings * VariableSettingsList::settings(const int index) const
{
    return (index < 0 || index >= mSettingsList.size())
            ? 0 : mSettingsList.at(index);
}

void VariableSettingsList::read(void)
{
    foreach (VariableSettings * vsi, mSettingsList)
        vsi->read(); // if flags?
}

QVariant VariableSettingsList::read(const VariableKey &key, const QVariant & defaultValue)
{
    foreach (VariableSettings * vsi, mSettingsList)
        if (vsi->contains(key))
            return vsi->read(key);
    return defaultValue;
}

void VariableSettingsList::write(void) const
{
    foreach (VariableSettings * vsi, mSettingsList)
        vsi->write();
}

void VariableSettingsList::write(const VariableKey &vid, const QVariant & newValue)
{
    foreach (VariableSettings * vsi, mSettingsList)
        if (vsi->contains(vid)) // && isWritable()??
        {
            vsi->write(vid, newValue);
            return;
        }
    mSettingsList.first()->write(vid, newValue);
}

void VariableSettingsList::set(const Variable & var)
{
    VariableKey key(var.key());
    foreach (VariableSettings * vsi, mSettingsList)
        if (vsi->contains(key))
        {
            vsi->set(var);
            return;
        }
    mSettingsList.first()->set(var);
}

void VariableSettingsList::set(const VariableKey &key, const QVariant & value)
{
    foreach (VariableSettings * vsi, mSettingsList)
        if (vsi->contains(key))
        {
            vsi->write(key, value);
            return;
        }
    mSettingsList.first()->write(key, value);
}

void VariableSettingsList::setDefault(const Variable & vbl)
{
    mpDefault->set(vbl);
}

void VariableSettingsList::setDefault(const VariableKey &key,
                                      const QVariant & value)
{
    mpDefault->set(key, value);
}

Variable VariableSettingsList::at(const VariableKey &key) const
{
    foreach (VariableSettings * vsi, mSettingsList)
        if (vsi->contains(key))
            return vsi->at(key);
    return Variable();
}

QVariant VariableSettingsList::value(const VariableKey &key) const
{
    foreach (VariableSettings * vsi, mSettingsList)
        if (vsi->contains(key))
            return vsi->value(key);
    return QVariant();
}

VariableSet VariableSettingsList::exportSection(const VariableKey &sectionKey) const
{
    VariableSet result("VariableSettingsList:" + sectionKey);
    int n = sectionKey.count();
    foreach (VariableSettings * vsi, mSettingsList)
    {
        foreach (VariableKey key, vsi->keys(sectionKey))
        {
            Variable vbl(vsi->at(key));
            VariableKey newKey(key.segments(n));
            if ( ! result.contains(newKey))
            {
                result.set(newKey, vbl.var());
            }
        }
    }
    return result;
}

void VariableSettingsList::start(void)
{
    stop();
    foreach (VariableKey key, mTriggerSet) set(key, QString());
    mpWatchTimer = new QTimer(this);
    mpWatchTimer->setInterval(mUpdateMsec ? mUpdateMsec : 20000);
    mpWatchTimer->start();
    emit (started());
}

void VariableSettingsList::stop(void)
{
    if (mpWatchTimer)
    {
        mpWatchTimer->deleteLater();
        mpWatchTimer = 0;
    }
    emit (stopped());
}

void VariableSettingsList::update(void)
{
    if (mIsUpdateRead)
    {
        read();
        foreach (VariableKey key, mTriggerSet)
        {
            QVariant var = value(key);
            if (isTrigger(key))
            {
                emit (triggered(key, var));
                set(key, QString());
            }
        }
        write();
    }
    else
    {
        foreach (VariableKey key, mTriggerSet)
        {
            QVariant var = read(key);
            if (isTrigger(key))
            {
                emit (triggered(key, var));
                write(key, QString());
            }
        }
    }
}
