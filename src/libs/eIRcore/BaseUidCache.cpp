#include "BaseUidCache.h"

#include "../eIRbase/MillisecondTime.h"

#include "BaseCacheWorker.h"

BaseUidCache::BaseUidCache(QObject *parent)
    : QObject{parent}
    , cmpWorker(new BaseCacheWorker(this))
{
    setObjectName("BaseUidCache");
}

bool BaseUidCache::contains(const Uid uid) const
{
    return mUidEntryMap.contains(uid);
}

Count BaseUidCache::count() const
{
    return mUidEntryMap.count();
}

bool BaseUidCache::isHeld(const Uid uid) const
{
    const BaseCacheEntry cBCE = read(uid);
    return cBCE.isHeld();
}

BaseCacheEntry BaseUidCache::read(const Uid uid) const
{
    return mUidEntryMap.value(uid);
}

Uid::List BaseUidCache::uidsInTouchOrder() const
{
    return mTouchEmsUidMap.values();
}

Uid BaseUidCache::add(const BaseCacheEntry &entry)
{
    const Uid cCacheUid = entry.uid().isNull() ? Uid(true) : entry.uid();
    mUidEntryMap.insert(cCacheUid, entry);
    mUidKeyDMap.insertUnique(cCacheUid, entry.ident().key());
    mTouchEmsUidMap.insert(MillisecondTime::current(), cCacheUid);
    return cCacheUid;
}

void BaseUidCache::remove(const Uid uid)
{
    const BaseCacheEntry cBCE = read(uid);
    if (cBCE.isHeld()) qWarning() << Q_FUNC_INFO << uid.tail() << "isHeld";
    const EpochMilliseconds cEms= cBCE.lastTouch();
    if (mTouchEmsUidMap.contains(cEms, uid))
        mTouchEmsUidMap.remove(cEms, uid);
    if (mUidKeyDMap.contains(uid))
        mUidKeyDMap.remove(uid);
    mUidEntryMap.remove(uid);
}
