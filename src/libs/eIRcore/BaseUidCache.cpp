#include "BaseUidCache.h"

#include "BaseCacheWorker.h"

BaseUidCache::BaseUidCache(QObject *parent)
    : QObject{parent}
    , cmpWorker(new BaseCacheWorker(this))
{
    setObjectName("BaseUidCache");
}

Uid::List BaseUidCache::uidsInTouchOrder() const
{
    return mTouchEmsUidMap.values();
}
