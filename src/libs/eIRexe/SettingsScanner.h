#pragma once
#include"eIRexe.h"

#include <QThread>

#include <QVariant>

//#include "Log.h"
class Settings;

class EIREXE_EXPORT SettingsScanner : public QThread
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

inline void SettingsScanner::done(const bool is)
{
    mDone = is;
}

