#include "BaseCacheEntry.h"

#include <QDateTime>

BaseCacheEntry::BaseCacheEntry() {;}
BaseCacheEntry::BaseCacheEntry(const Key &entryKey, const Id id) : mIdent(entryKey, id) {;}

Uid BaseCacheEntry::uid() const
{
    return ident().uid();
}

bool BaseCacheEntry::contains(const Key &valueKey) const
{
    return mKeyMap.contains(valueKey);
}

bool BaseCacheEntry::isHeld() const
{
    return ! mHolderList.isEmpty();
}

QVariant BaseCacheEntry::get(const Key &valueKey) const
{
    return mKeyMap.value(valueKey);
}

void BaseCacheEntry::uid(const Uid aUid)
{
    mIdent.uid(aUid);
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

void BaseCacheEntry::set(const Key &valueKey, const QVariant &value)
{
    mKeyMap.set(valueKey, value);
}

