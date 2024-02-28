#pragma once

#include <QVariant>

#include "Settings.h"

class Setting : public QVariant
{
public:
    Setting(Settings * Parent,
            const QString & Key,
            QVariant defalt,
            Settings::Flags F=Settings::$null);
    ~Setting();

    QString keyName(void) const { return mKey; }
    void setValue(const QVariant & value);
    Settings::Flags & flags(); // non-const


private:
    Settings *	mpSettings=nullptr;
    QString mKey;
    Settings::Flags mFlags;

// ----------------- properties ----------------
public:
    bool getWriteBack() const;
    void setWriteBack(bool new_WriteBack);
    bool getAdvancedMode() const;
    void setAdvancedMode(bool new_AdvancedMode);
    int getUpdateMsec() const;
    void setUpdateMsec(int new_UpdateMsec);
    int getPollCount() const;
    void setPollCount(int new_PollCount);
signals:
    void changed_WriteBack(bool WriteBack);
    void changed_AdvancedMode(bool AdvancedMode);
    void changed_UpdateMsec(int UpdateMsec);
    void changed_PollCount(int PollCount);
private:
    bool m_WriteBack;
    bool m_AdvancedMode;
    int m_UpdateMsec;
    int m_PollCount;
    Q_PROPERTY(int WriteBack READ getWriteBack WRITE setWriteBack NOTIFY changed_WriteBack FINAL)
    Q_PROPERTY(int AdvancedMode READ getAdvancedMode WRITE setAdvancedMode NOTIFY changed_AdvancedMode FINAL)
    Q_PROPERTY(int UpdateMsec READ getUpdateMsec WRITE setUpdateMsec NOTIFY changed_UpdateMsec FINAL)
    Q_PROPERTY(int PollCount READ getPollCount WRITE setPollCount NOTIFY changed_PollCount FINAL)
};

inline Settings::Flags &Setting::flags()
{
    return mFlags;
}

inline bool Setting::getWriteBack() const
{
    return m_WriteBack;
}

inline void Setting::setWriteBack(bool new_WriteBack)
{
    if (m_WriteBack == new_WriteBack)
        return;
    m_WriteBack = new_WriteBack;
    emit changed_WriteBack(m_WriteBack);
}

inline bool Setting::getAdvancedMode() const
{
    return m_AdvancedMode;
}

inline void Setting::setAdvancedMode(bool new_AdvancedMode)
{
    if (m_AdvancedMode == new_AdvancedMode)
        return;
    m_AdvancedMode = new_AdvancedMode;
    emit changed_AdvancedMode(m_AdvancedMode);
}

inline int Setting::getUpdateMsec() const
{
    return m_UpdateMsec;
}

inline void Setting::setUpdateMsec(int new_UpdateMsec)
{
    if (m_UpdateMsec == new_UpdateMsec)
        return;
    m_UpdateMsec = new_UpdateMsec;
    emit changed_UpdateMsec(m_UpdateMsec);
}

inline int Setting::getPollCount() const
{
    return m_PollCount;
}

inline void Setting::setPollCount(int new_PollCount)
{
    if (m_PollCount == new_PollCount)
        return;
    m_PollCount = new_PollCount;
    emit changed_PollCount(m_PollCount);
}
