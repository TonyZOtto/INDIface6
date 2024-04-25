#include "KeyMap.h"

KeyMap::KeyMap() {}

const QVariant KeyMap::value(const Key &key) const
{
    return mKeyVariantMap.value(key);
}

const Key::List KeyMap::keys() const
{
    return mKeyVariantMap.keys();
}

void KeyMap::insert(const Key &key, const QVariant &var)
{
    mKeyVariantMap.insert(key, var);
}

void KeyMap::insert(const KeyMap &other, const Key &groupKey)
{
    foreach (Key tKey, other.keys())
    {
        const QVariant cVar = other.value(tKey);
        tKey.prepend(groupKey);
        insert(tKey, cVar);
    }
}
