#include "IfCache.h"

IfCache::IfCache(QObject *parent)
    : BaseUidCache{parent}
{
    setObjectName("IfCache");
}

Uid IfCache::frame(const FrameData &frd)
{
    const Uid cCacheUid = frd.frameUid().isNull() ? Uid(true) : frd.frameUid();
    BaseCacheEntry tBCE(frd.frameKey());
    tBCE.ident(frd.ident());
    return cCacheUid;
}
