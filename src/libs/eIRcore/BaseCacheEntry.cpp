#include "BaseCacheEntry.h"

#include <QDateTime>

BaseCacheEntry::BaseCacheEntry() : mIdent(Uid::CacheEntry) {;}
BaseCacheEntry::BaseCacheEntry(const Key &entryKey, const Id id)
    : mIdent(Uid::CacheEntry, entryKey, id) {;}

bool BaseCacheEntry::contains(const Key &valueKey) const
{
    return mKeyMap.contains(valueKey);
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

