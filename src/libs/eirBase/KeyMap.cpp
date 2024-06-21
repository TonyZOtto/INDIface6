#include "KeyMap.h"

KeyMap::KeyMap() {}
KeyMap::KeyMap(const Ident aIdent) : mIdent(aIdent) {;}
KeyMap::KeyMap(const Key aKey) : mIdent(aKey) {;}

bool KeyMap::contains(const Key &key) const
{
    return mKeyVariantMap.contains(key);
}

QVariant KeyMap::get(const Key &aKey) const
{
    return contains(aKey) ? value(aKey) : QVariant();
}

QVariant KeyMap::get(const Key &aKey, const QVariant &aDefault) const
{
    return contains(aKey) ? value(aKey) : aDefault;
}

const QVariant KeyMap::value(const Key &aKey) const
{
    return mKeyVariantMap.value(aKey);
}

const QVariant KeyMap::value(const Key &aKey, const QVariant &aDefault) const
{
    return contains(aKey) ? value(aKey) : aDefault;
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
