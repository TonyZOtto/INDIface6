#pragma once

#include <QObject>
#include <QThread>

class Settings;

class SettingsScanner : public QThread
{
    Q_OBJECT
public:
    explicit SettingsScanner(Settings *parent=nullptr);

public: // non-const
    void done(const bool is);

protected:
    virtual void run();

signals:
    void changeProperty(QString key, QVariant var);

private:
    Settings * mpSettings=nullptr;
    bool mDone=false;
};

