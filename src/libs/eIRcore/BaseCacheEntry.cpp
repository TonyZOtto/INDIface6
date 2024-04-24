#include "BaseCacheEntry.h"

#include <QDateTime>

BaseCacheEntry::BaseCacheEntry() {;}
BaseCacheEntry::BaseCacheEntry(const Key &entryKey, const Id id) : mIdent(entryKey, id) {;}

bool BaseCacheEntry::contains(const Key &valueKey) const
{
    return mKeyMap.contains(valueKey);
}

bool BaseCacheEntry::isHeld() const
{
    return ! mHolderList.isEmpty();
}

QVariant BaseCacheEntry::read(const Key &valueKey) const
{
    return mKeyMap.value(valueKey);
}

void BaseCacheEntry::set(const Ident &i)
{
    mIdent = i;
}

void BaseCacheEntry::hold(void *holder)
{
    mHolderList.append(holder);
}

void BaseCacheEntry::release(void *holder)
{
    mHolderList.removeOne(holder);
}

void BaseCacheEntry::touch()
{
    mLastTouchEms = QDateTime::currentMSecsSinceEpoch();
}

void BaseCacheEntry::write(const Key &valueKey, const QVariant &value)
{
    mKeyMap.insert(valueKey, value);
}

