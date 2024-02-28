#include "SettingsScanner.h"

#include <QVariant>

#include "Settings.h"

SettingsScanner::SettingsScanner(Settings * parent)
    : QThread((QObject *)parent)
    , mpSettings(parent)
    , mDone(false)
{
    setObjectName("SettingsScanner");
}

void SettingsScanner::run(void)
{
    int msSleep = 10000;

    for (;;)
    {
        if (mDone || 0 == msSleep)
        {
            if ( ! mpSettings->pollCountKey().isEmpty())
                mpSettings->setValue(mpSettings->pollCountKey(), "-1");
            return;
        }

        msleep(msSleep);

        if (mDone || 0 == msSleep)
        {
            if ( ! mpSettings->pollCountKey().isEmpty())
                mpSettings->setValue(mpSettings->pollCountKey(), "-1");
            return;
        }
        mpSettings->scanForUpdate();
        if (0 == mpSettings->updateMsec())
        {
            msSleep = 10000;
            continue;
        }
        mpSettings->scan();

        msSleep = mpSettings->updateMsec() ? mpSettings->updateMsec() : 10000;
    }
} // run()

