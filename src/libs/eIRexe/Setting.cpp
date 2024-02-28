#include "Setting.h"

#include <QTimer>

#include "Settings.h"

Setting::Setting(Settings * Parent,
                 const QString & Key,
                 QVariant defalt,
                 Settings::Flags f)
    : QVariant(defalt)
    , mpSettings(Parent)
    , mKey(Key)
    , mFlags(f)
{
    mpSettings->construct(this);
}

Setting::~Setting()
{
    mpSettings->destruct(this);
}

void Setting::setValue(const QVariant & value)
{
    if (*(QVariant *)this != value)
    {
        *(QVariant *)this = value;
        mFlags |= Settings::Dirty | Settings::Changed;
        mpSettings->emitValueChanged(mKey);
    }
} // setValue()
