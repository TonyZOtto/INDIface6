#pragma once

#include "BaseSettingsObject.h"

class OutputSettings : public BaseSettingsObject
{
    Q_OBJECT
public:
    explicit OutputSettings(QObject *parent = nullptr);

public:
    virtual AText groupName() const { return "Input"; }
    QUrl url() const;

    // ========================== Properties ========================
    QString LogUrls() const;
    void LogUrls(const QString &new_LogUrls);
    QString BaseDir() const;
    void BaseDir(const QString &new_BaseDir);
    QString CaptureFrameDir() const;
    void CaptureFrameDir(const QString &new_CaptureFrameDir);
    QString InputFrameDir() const;
    void InputFrameDir(const QString &new_InputFrameDir);
    QString MarkedFrameDir() const;
    void MarkedFrameDir(const QString &new_MarkedFrameDir);
signals:
    void changed_LogUrls();
    void changed_BaseDir();
    void changed_CaptureFrameDir();
    void changed_InputFrameDir();
    void changed_MarkedFrameDir();
private:
    QString m_LogUrls;
    QString m_BaseDir;
    QString m_CaptureFrameDir;
    QString m_InputFrameDir;
    QString m_MarkedFrameDir;
    Q_PROPERTY(QString LogUrls READ LogUrls WRITE LogUrls NOTIFY changed_LogUrls FINAL)
    Q_PROPERTY(QString BaseDir READ BaseDir WRITE BaseDir NOTIFY changed_BaseDir FINAL)
    Q_PROPERTY(QString CaptureFrameDir READ CaptureFrameDir WRITE CaptureFrameDir NOTIFY changed_CaptureFrameDir FINAL)
    Q_PROPERTY(QString InputFrameDir READ InputFrameDir WRITE InputFrameDir NOTIFY changed_InputFrameDir FINAL)
    Q_PROPERTY(QString MarkedFrameDir READ MarkedFrameDir WRITE MarkedFrameDir NOTIFY changed_MarkedFrameDir FINAL)
};

inline QString OutputSettings::LogUrls() const
{
    return m_LogUrls;
}

inline void OutputSettings::LogUrls(const QString &new_LogUrls)
{
    if (m_LogUrls == new_LogUrls)
        return;
    m_LogUrls = new_LogUrls;
    emit changed_LogUrls();
}

inline QString OutputSettings::BaseDir() const
{
    return m_BaseDir;
}

inline void OutputSettings::BaseDir(const QString &new_BaseDir)
{
    if (m_BaseDir == new_BaseDir)
        return;
    m_BaseDir = new_BaseDir;
    emit changed_BaseDir();
}

inline QString OutputSettings::CaptureFrameDir() const
{
    return m_CaptureFrameDir;
}

inline void OutputSettings::CaptureFrameDir(const QString &new_CaptureFrameDir)
{
    if (m_CaptureFrameDir == new_CaptureFrameDir)
        return;
    m_CaptureFrameDir = new_CaptureFrameDir;
    emit changed_CaptureFrameDir();
}

inline QString OutputSettings::InputFrameDir() const
{
    return m_InputFrameDir;
}

inline void OutputSettings::InputFrameDir(const QString &new_InputFrameDir)
{
    if (m_InputFrameDir == new_InputFrameDir)
        return;
    m_InputFrameDir = new_InputFrameDir;
    emit changed_InputFrameDir();
}

inline QString OutputSettings::MarkedFrameDir() const
{
    return m_MarkedFrameDir;
}

inline void OutputSettings::MarkedFrameDir(const QString &new_MarkedFrameDir)
{
    if (m_MarkedFrameDir == new_MarkedFrameDir)
        return;
    m_MarkedFrameDir = new_MarkedFrameDir;
    emit changed_MarkedFrameDir();
}
