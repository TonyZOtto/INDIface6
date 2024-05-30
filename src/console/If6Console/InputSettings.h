#pragma once

#include "BaseSettingsObject.h"

#include <Types.h>

class InputSettings : public BaseSettingsObject
{
    Q_OBJECT
public:
    explicit InputSettings(QObject *parent = nullptr);

public:
    virtual AText groupName() const { return "Input"; }
    QUrl url() const;

    // ========================== Properties ========================
private:
    Q_PROPERTY(QString Url READ Url WRITE Url NOTIFY changed_Url FINAL)
    Q_PROPERTY(EpochMilliseconds SampleMsec READ SampleMsec WRITE SampleMsec NOTIFY changed_SampleMsec FINAL)
    Q_PROPERTY(bool DeleteAfter READ DeleteAfter WRITE DeleteAfter RESET reset_DeleteAfter NOTIFY changed_DeleteAfter FINAL)
public:
    QString Url() const;
    void Url(const QString &new_Url);
    EpochMilliseconds SampleMsec() const;
    void SampleMsec(EpochMilliseconds new_SampleMsec);
    bool DeleteAfter() const;
    void DeleteAfter(bool new_DeleteAfter);
    void reset_DeleteAfter();
signals:
    void changed_Url();
    void changed_SampleMsec();
    void changed_DeleteAfter();
private:
    QString m_Url;
    EpochMilliseconds m_SampleMsec;
    bool m_DeleteAfter;
};

inline QString InputSettings::Url() const
{
    return m_Url;
}

inline void InputSettings::Url(const QString &new_Url)
{
    if (m_Url == new_Url)
        return;
    m_Url = new_Url;
    emit changed_Url();
}

inline EpochMilliseconds InputSettings::SampleMsec() const
{
    return m_SampleMsec;
}

inline void InputSettings::SampleMsec(EpochMilliseconds new_SampleMsec)
{
    if (m_SampleMsec == new_SampleMsec)
        return;
    m_SampleMsec = new_SampleMsec;
    emit changed_SampleMsec();
}

inline bool InputSettings::DeleteAfter() const
{
    return m_DeleteAfter;
}

inline void InputSettings::DeleteAfter(bool new_DeleteAfter)
{
    if (m_DeleteAfter == new_DeleteAfter)
        return;
    m_DeleteAfter = new_DeleteAfter;
    emit changed_DeleteAfter();
}

inline void InputSettings::reset_DeleteAfter()
{
    DeleteAfter(false);
}
