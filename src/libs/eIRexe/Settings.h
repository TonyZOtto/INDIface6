#pragma once
#include "eIRexe.h"

#include <QSettings>

#include <QMap>
#include <QVariant>
class QTimer;

class Setting;
class SettingProperty;
class SettingsScanner;

class EIREXE_EXPORT Settings : public QSettings
{
    Q_OBJECT
public: // types
    enum Flag
    {
        $null       = 0,
        Volatile	= 0x00000001,
        ReadOnly	= 0x00000002,
        Advanced	= 0x00000004,
        Hidden		= 0x00000008,
        WidgetState	= 0x00000100,
        Geometry	= 0x00000200,
        Dirty		= 0x00010000,
        Changed		= 0x00020000,
    };
    Q_DECLARE_FLAGS(Flags, Flag)

public: // ctors
    Settings(QObject * parent=nullptr);
    Settings(const QString & organization,
             const QString & application = QString(),
             QObject * parent = 0);
    Settings(const QString & iniFilename,
             QObject * parent);
    ~Settings();

public: // overrides
    QVariant value(const QString & key, const QVariant &defalt=QVariant()) const;
    void setValue(const QString & key, const QVariant &newValue);

public: // const
    const QString pollCountKey() const;
    const QString updateMsecKey() const;

public slots:
    void startTimers(void);
    void scanForUpdate(void);
    void scan(void);
    void emitValueChanged(QString key);
    void emitPropertyChanged(QString key);

public: // non-const
    void setPollCountKey(const QString & key, int count=0);
    void updatePollCount();
    void objectProperties(QObject * Object,
                          const QString & BaseKey,
                          const QList<QByteArray> & PropertyNames,
                          Flags F=$null);
    void objectProperty(QObject * Object, const QString & BaseKey,
                        const QString & PropertyName, Flags f=$null);
    void objectProperty(const QString & Key, QObject * Object,
                        const QString & PropertyName, Flags f=$null);
    void construct(Setting * child);
    void destruct(Setting * child);

signals:
    void valueChanged(QString key);
    void propertyChanged(QString key);
    void scanStart(void);
    void scanFinish(void);


private:
    QMap<QString, Setting *> mVars;
    QMap<QString, SettingProperty *> mProps;
    QMap<QString, QString> mOpts;
    QString mPollCountKey;
    QString mUpdateMsecKey;

    SettingsScanner * scanner=nullptr;
    QTimer * timerUpdate=nullptr;
    QTimer * timerScan=nullptr;


public: // -------------- properties --------------
    bool advancedMode() const;
    int updateMsec() const;
    int pollCount() const;

public slots:
    void advancedMode(bool new_advancedMode);
    void reset_advancedMode();
    void updateMsec(int new_updateMsec);
    void reset_updateMsec();

signals:
    void changed_advancedMode(bool advancedMode);
    void changed_updateMsec(int updateMsec);

private:
    bool m_advancedMode;
    int m_updateMsec;
    int m_pollCount;

    Q_PROPERTY(bool advancedMode READ advancedMode WRITE advancedMode RESET reset_advancedMode NOTIFY changed_advancedMode FINAL)
    Q_PROPERTY(int updateMsec READ updateMsec WRITE updateMsec RESET reset_updateMsec NOTIFY changed_updateMsec FINAL)
    Q_PROPERTY(int pollCount READ pollCount CONSTANT FINAL)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Settings::Flags);

// -------------- properties --------------

inline const QString Settings::pollCountKey() const
{
    return mPollCountKey;
}

inline const QString Settings::updateMsecKey() const
{
    return mUpdateMsecKey;
}

inline bool Settings::advancedMode() const
{
    return m_advancedMode;
}

inline void Settings::advancedMode(bool new_advancedMode)
{
    if (m_advancedMode == new_advancedMode)
        return;
    m_advancedMode = new_advancedMode;
    emit changed_advancedMode(m_advancedMode);
}

inline void Settings::reset_advancedMode()
{
    advancedMode({}); // TODO: Adapt to use your actual default value
}

inline int Settings::updateMsec() const
{
    return m_updateMsec;
}

inline void Settings::updateMsec(int new_updateMsec)
{
    if (m_updateMsec == new_updateMsec)
        return;
    m_updateMsec = new_updateMsec;
    emit changed_updateMsec(m_updateMsec);
}

inline void Settings::reset_updateMsec()
{
    updateMsec({}); // TODO: Adapt to use your actual default value
}

inline int Settings::pollCount() const
{
    return m_pollCount;
}
