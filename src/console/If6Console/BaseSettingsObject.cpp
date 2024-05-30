#include "BaseSettingsObject.h"

BaseSettingsObject::BaseSettingsObject(QObject *parent)
    : QObject{parent}
{
    setObjectName("BaseSettingsObject");
}
