#include "Settings.h"

#include <QSettings>
#include <QTimer>

#include "Setting.h"
#include "SettingProperty.h"
#include "SettingsScanner.h"

Settings::Settings(const QString & organization,
                   const QString & application,
                   QObject * parent)
    : QSettings(organization, application, parent)
{
    setObjectName("Settings:" + organization + "/" + application);
}

Settings::Settings(const QString &iniFilename, QObject *parent)
    : QSettings(iniFilename, QSettings::IniFormat, parent)
{
    setObjectName("Settings:" + iniFilename);
}

Settings::~Settings()
{
    delete mpScanTimer;
    delete mpUpdateTimer;

    if (mpScanner)
    {
        mpScanner->done(true);
        mpScanner->wait(10000);
        if ( ! mpScanner->isFinished())
            mpScanner->terminate();
    }
}

QVariant Settings::value(const QString &key, const QVariant &defalt) const
{
    if (mVars.contains(key)) return *mVars[key];
    if (mProps.contains(key)) return mProps[key]->value();
    return defalt;
}

void Settings::setValue(const QString &key, const QVariant &newValue)
{
    if (mVars.contains(key))
    {
        Setting * var = mVars[key];
        *(QVariant *)var = newValue;
    }
    else if (mProps.contains(key))
    {
        SettingProperty * prop = mProps.value(key);
        *(QVariant *)prop = newValue;
    }
    QSettings::setValue(key, newValue);
}

void Settings::insert(const SettingsMap &map)
{
    foreach(const QString cKey, map.keys())
    {
        const QVariant cValue = map.value(cKey);
        setValue(cKey, cValue);
    }
}

void Settings::startTimers(void)
{
    if (mpUpdateTimer)
    {
        delete mpUpdateTimer;
        mpUpdateTimer = 0;
    }
    if (mpScanTimer)
    {
        delete mpScanTimer;
        mpScanTimer = 0;
    }

    mpUpdateTimer = new QTimer(this);
    mpScanTimer = new QTimer(this);

    mpUpdateTimer->setInterval(20000);
    connect(mpUpdateTimer, SIGNAL(timeout()), this, SLOT(scanForUpdate()));

    mpScanTimer->setInterval(updateMsec());
    if (updateMsec())
    {
        connect(mpScanTimer, SIGNAL(timeout()), this, SLOT(scan()));
        mpScanTimer->start();
    }

    mpUpdateTimer->start();
} // startTimers()

void Settings::scanForUpdate()
{
    const int tUpdateMsec = QSettings::value(updateMsecKey()).toInt();
    if (m_updateMsec != tUpdateMsec)
    {
        m_updateMsec = tUpdateMsec;
        if (m_updateMsec)
            scan();
    }
}

void Settings::scan()
{
    foreach (QString tKey, mVars.keys())
    {
        Setting * pSetting = mVars.value(tKey);
        const QString cOldValue = pSetting->toString();
        const QString cNewValue = value(tKey).toString();
        if (cNewValue != cOldValue)
        {
            emitValueChanged(tKey);
            pSetting->setValue(cNewValue);
        }
    }
    foreach (QString tKey, mProps.keys())
    {
        SettingProperty * pSetting = mProps.value(tKey);
        const QString cOldValue = pSetting->value().toString();
        const QString cNewValue = value(tKey).toString();
        if (cNewValue != cOldValue)
        {
            emitPropertyChanged(tKey);
            pSetting->setValue(cNewValue);
        }
    }
    updatePollCount();
}

void Settings::emitValueChanged(QString key)
{
    emit valueChanged(key);
}

void Settings::emitPropertyChanged(QString key)
{
    emit propertyChanged(key);
}

void Settings::setPollCountKey(const QString & key, int count)
{
    if (key.isEmpty())
        disconnect(this, SIGNAL(scanFinish()), this, SLOT(updatePollCount()));
    else
        connect(this, SIGNAL(scanFinish()), this, SLOT(updatePollCount()));
    mPollCountKey = key;
    m_pollCount = count;
    updatePollCount();
}

void Settings::updatePollCount(void)
{
    this->setValue(mPollCountKey, QString::number(m_pollCount));
    ++m_pollCount;
}

void Settings::objectProperties(QObject *Object, const QString &BaseKey, const QList<QByteArray> &PropertyNames, Flags F)
{
    foreach(QString n, PropertyNames)
        objectProperty(Object, BaseKey, n, F);
}

void Settings::objectProperty(QObject * Object, const QString & BaseKey,
                              const QString & PropertyName, Flags f)
{
    QString key = BaseKey + (BaseKey.isEmpty() ? "" : "/") + PropertyName;
    objectProperty(key, Object, PropertyName, f);
}

void Settings::objectProperty(const QString & Key,
                              QObject * Object,
                              const QString & PropertyName,
                              Settings::Flags f)
{
    SettingProperty * child = new SettingProperty(this, Object, Key, PropertyName, f);
    mProps.insert(Key.toLower(), child);
    QVariant tDef = Object->property(qPrintable(PropertyName));
    QVariant tVar = value(Key, tDef);
    child->setValue(tVar);
    if (tVar != tDef)
        Object->setProperty(qPrintable(PropertyName), tVar);
    QString mapKey = Key.toLower();
    if (mOpts.contains(mapKey))
    {
        Object->setProperty(qPrintable(PropertyName), mOpts.value(mapKey));
        mOpts.remove(mapKey);
        child->mFlags |= Settings::Dirty | Settings::Changed;
    }
    if (this == Object && 0 == PropertyName.compare(tr("UpdateMsec", "config"), Qt::CaseInsensitive))
        mUpdateMsecKey = Key;
}

void Settings::construct(Setting * child)
{
    mVars[child->keyName().toLower()] = child;
    QVariant tDef = *child;
    QVariant tVar = value(child->keyName(), tDef);
    child->setValue(tVar);
    QString key = child->keyName().toLower();
    if (mOpts.contains(child->keyName()))
    {
        *(QVariant *)child = mOpts.value(child->keyName());
        mOpts.remove(child->keyName());
        child->flags() |= Settings::Dirty | Settings::Changed;
    }
}

void Settings::destruct(Setting * child)
{
    if ( ! child->flags().testFlag(ReadOnly)
        && child->flags().testFlag(Dirty))
    {
        QVariant var = *child;
        setValue(child->keyName(), var.toString());
    }
    mVars.remove(child->keyName().toLower());
}

QString Settings::source() const
{
    QString result("{unknown}");
#if 1
    switch (format())
    {
    case QSettings::Registry32Format:
    case QSettings::Registry64Format:
    case QSettings::NativeFormat:
        result = QString("%3:%1/%2").arg(organizationName(), applicationName(),
                    scope() ? "HKLM" : "HKCU");
        break;
    case QSettings::IniFormat:
        result = fileName();
        break;
    case QSettings::InvalidFormat:
    default:
        // leave unknown
#ifndef Q_OS_WINDOWS
        Q_ASSERT(!"NEEDDO: Linux"); break; // NEEDDO Linux
#endif
        break;
    }
#endif
    return result;
}

QStringList Settings::debugStrings() const
{
    QStringList result;
    result << QString("===Settings: %1 [%2]").arg(source()).arg(format());
    if ( ! mVars.isEmpty())
    {
        result << "---Vars: " + QString::number(mVars.count());
        foreach (const QString cKey, mVars.keys())
            result << "   " + cKey + "=" + mVars[cKey]->toString();
    }
    if ( ! mProps.isEmpty())
    {
        result << "---Props: " + QString::number(mProps.count());
        foreach (const QString cKey, mProps.keys())
            result << "   " + cKey + "=" + mProps[cKey]->value().toString();
    }
    if ( ! mOpts.isEmpty())
    {
        result << "---Options: " + QString::number(mOpts.count());
        foreach (const QString cKey, mOpts.keys())
            result << "   " + cKey + "=" + mOpts[cKey];
    }
    return result;
}
