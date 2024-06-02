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
public:
    QString Url() const;
    void Url(const QString &new_Url);
    QString ImageId() const;
    void ImageId(const QString &new_ImageId);
    unsigned int FramesProcessed() const;
    void FramesProcessed(unsigned int new_FramesProcessed);
    void reset_FramesProcessed();
    unsigned int NullFrames() const;
    void NullFrames(unsigned int new_NullFrames);
    void reset_NullFrames();
    QString Processing() const;
    void Processing(const QString &new_Processing);
signals:
    void changed_Url();
    void changed_ImageId();
    void changed_FramesProcessed();
    void changed_NullFrames();
    void changed_Processing();
private:
    QString m_Url;
    QString m_ImageId;
    unsigned m_FramesProcessed;
    unsigned m_NullFrames;
    QString m_Processing;
    Q_PROPERTY(QString Url READ Url WRITE Url NOTIFY changed_Url FINAL)
    Q_PROPERTY(QString ImageId READ ImageId WRITE ImageId NOTIFY changed_ImageId FINAL)
    Q_PROPERTY(unsigned int FramesProcessed READ FramesProcessed WRITE FramesProcessed RESET reset_FramesProcessed NOTIFY changed_FramesProcessed FINAL)
    Q_PROPERTY(unsigned int NullFrames READ NullFrames WRITE NullFrames RESET reset_NullFrames NOTIFY changed_NullFrames FINAL)
    Q_PROPERTY(QString Processing READ Processing WRITE Processing NOTIFY changed_Processing FINAL)
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

inline QString InputSettings::ImageId() const
{
    return m_ImageId;
}

inline void InputSettings::ImageId(const QString &new_ImageId)
{
    if (m_ImageId == new_ImageId)
        return;
    m_ImageId = new_ImageId;
    emit changed_ImageId();
}

inline unsigned int InputSettings::FramesProcessed() const
{
    return m_FramesProcessed;
}

inline void InputSettings::FramesProcessed(unsigned int new_FramesProcessed)
{
    if (m_FramesProcessed == new_FramesProcessed)
        return;
    m_FramesProcessed = new_FramesProcessed;
    emit changed_FramesProcessed();
}

inline void InputSettings::reset_FramesProcessed()
{
    FramesProcessed({}); // TODO: Adapt to use your actual default value
}

inline unsigned int InputSettings::NullFrames() const
{
    return m_NullFrames;
}

inline void InputSettings::NullFrames(unsigned int new_NullFrames)
{
    if (m_NullFrames == new_NullFrames)
        return;
    m_NullFrames = new_NullFrames;
    emit changed_NullFrames();
}

inline void InputSettings::reset_NullFrames()
{
    NullFrames({}); // TODO: Adapt to use your actual default value
}

inline QString InputSettings::Processing() const
{
    return m_Processing;
}

inline void InputSettings::Processing(const QString &new_Processing)
{
    if (m_Processing == new_Processing)
        return;
    m_Processing = new_Processing;
    emit changed_Processing();
}
