#include "Settings.h"

#include <QSettings>
#include <QTimer>

#include "Setting.h"
#include "SettingProperty.h"
#include "SettingsScanner.h"

Settings::Settings(QObject * parent)
    : QObject(parent)
{
    setObjectName("Settings");
}

Settings::~Settings()
{
    delete timerScan;
    delete timerUpdate;

    if (scanner)
    {
        scanner->done(true);
        scanner->wait(10000);
        if ( ! scanner->isFinished())
            scanner->terminate();
    }
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue) const
{
    if (vars.contains(key)) return *vars[key];
    if (properties.contains(key)) return *properties[key];
}

void Settings::setValue(const QString &key, const QVariant &newValue) const
{
    if (vars.contains(key))
    {
        Setting * var = vars[key];
        *(QVariant *)var = newValue;
    }
    else if (properties.contains(key))
    {
        SettingProperty * prop = properties.value(key);
        *(QVariant *)prop = newValue;
    }
    QSettings::setValue(key, newValue);
}

void Settings::startTimers(void)
{
    if (timerUpdate)
    {
        delete timerUpdate;
        timerUpdate = 0;
    }
    if (timerScan)
    {
        delete timerScan;
        timerScan = 0;
    }

    timerUpdate = new QTimer(this);
    timerScan = new QTimer(this);

    timerUpdate->setInterval(20000);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(scanForUpdate()));

    timerScan->setInterval(updateMsec());
    if (updateMsec())
    {
        connect(timerScan, SIGNAL(timeout()), this, SLOT(scan()));
        timerScan->start();
    }

    timerUpdate->start();
} // startTimers()

void Settings::scanForUpdate()
{
    const int tUpdateMsec = QSettings::value(keyForUpdateMsec());
    if (m_updateMsec != tUpdateMsec)
    {
        m_updateMsec = tUpdateMsec;
        if (m_updateMsec)
            scan();
    }
}

void Settings::scan()
{
    foreach (QString tKey, vars.keys())
    {
        Setting * pSetting = vars.value(tKey);
        const QString cOldValue = pSetting->toString();
        const QString cNewValue = value(tKey).toString();
        if (cNewValue != cOldValue)
        {
            emitValueChanged(tKey);
            vars[tKey] = cNewValue;
        }
    }

    foreach (QString tKey, properties.keys())
    {
        SettingProperty * pSetting = properties.value(tKey);
        const QString cValue = QSettings::value(tKey).toString();
        if (vars.value(tKey) != cValue)
        {
            emitValueChanged(tKey);
            vars[tKey] = cValue;
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
    m_pollCountKey = key;
    m_pollCount = count;
    updatePollCount();
}

void Settings::updatePollCount(void)
{
    this->setValue(m_pollCountKey, QString::number(m_pollCount));
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

void Settings::objectProperty(const QString & Key, QObject * Object,
                    const QString & PropertyName, Settings::Flags f)
{
    SettingProperty * child = new SettingProperty(this, Object, Key, PropertyName, f);
    properties.insert(Key.toLower(), child);
    QVariant def = Object->property(qPrintable(PropertyName));
    QVariant var = value(Key, def);
    child->value = var;
    if (var != def)
        Object->setProperty(qPrintable(PropertyName), var);
    QString mapKey = Key.toLower();
    if (opts.contains(mapKey))
    {
        Object->setProperty(qPrintable(PropertyName), opts.value(mapKey));
        opts.remove(mapKey);
        child->mFlags |= Settings::Dirty | Settings::Changed;
    }
    if (this == Object && 0 == PropertyName.compare(tr("UpdateMsec", "config"), Qt::CaseInsensitive))
        keyForUpdateMsec = Key;
}

void Settings::construct(Setting * child)
{
    vars[child->keyName().toLower()] = child;
    QVariant def = *child;
    QVariant var = value(child->keyName(), def);
    *(QVariant *)child = var;
    QString key = child->keyName().toLower();
    if (opts.contains(child->keyName()))
    {
        *(QVariant *)child = opts.value(child->keyName());
        opts.remove(child->keyName());
        child->flags() |= Settings::Dirty | Settings::Changed;
    }

}

void Settings::destruct(Setting * child)
{
    if (writeBack()
        && ! child->flags.testFlag(ReadOnly)
        && child->flags.testFlag(Dirty))
    {
        QVariant var = *child;
        setValue(child->keyName(), var.toString());
    }
    vars.remove(child->keyName().toLower());

}
