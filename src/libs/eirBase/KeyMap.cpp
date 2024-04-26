#include "KeyMap.h"

KeyMap::KeyMap() {}

bool KeyMap::contains(const Key &key) const
{
    return mKeyVariantMap.contains(key);
}

const QVariant KeyMap::value(const Key &key) const
{
    return mKeyVariantMap.value(key);
}

const QVariant KeyMap::value(const Key &key, const QVariant &defalt) const
{
    return contains(key) ? value(key) : defalt;
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
