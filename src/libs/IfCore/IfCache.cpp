#include "IfCache.h"

IfCache::IfCache(QObject *parent)
    : BaseUidCache{parent}
{
    setObjectName("IfCache");
}

Uid IfCache::frame(const FrameData &aFrameData)
{
    FrameData tFrameData = aFrameData;
    Ident tIdent = aFrameData.ident();
    const Uid cCacheUid = tIdent.uid().isNull()
                              ? Uid(true)
                              : aFrameData.frameUid();
    tIdent.uid(cCacheUid);
    const Key cKey = tFrameData.frameKey();
    tIdent.key(cKey);
    BaseCacheEntry tBCE(cKey);
    tIdent.id(tBCE.ident().id());
    tFrameData.ident(tIdent);
    tBCE.ident(tIdent);
    tBCE.map(tFrameData);
    return cCacheUid;
}
