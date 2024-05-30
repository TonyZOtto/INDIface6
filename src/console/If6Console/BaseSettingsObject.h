#pragma once

#include <QObject>

#include <AText.h>

class Settings;

class BaseSettingsObject : public QObject
{
    Q_OBJECT
public:
    explicit BaseSettingsObject(QObject *parent = nullptr);

public:
    virtual AText groupName() const = 0;

public:
    bool read(Settings * stgs);
    bool write(Settings * stgs);

signals:
    void itemChanged(const AText itemName, const QVariant newValue, const QVariant oldValue);
    void readFinished(const AText groupName, const bool success);
    void writeFinished(const AText groupName, const bool success);
};
