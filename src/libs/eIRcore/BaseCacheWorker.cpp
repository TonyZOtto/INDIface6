#include "BaseCacheWorker.h"

#include "BaseUidCache.h"

BaseCacheWorker::BaseCacheWorker(BaseUidCache *parent)
    : QThread{parent}
    , mpCache(parent)
    , mShutdown(false)
{
    setObjectName("BaseCacheWorker:"+cache()->objectName());
    start(QThread::LowPriority);
}

void BaseCacheWorker::run()
{
    while ( ! mShutdown)
    {
        if (mUidQueue.isEmpty())
        {
            enqueueAll();
            msleep(mLongSleep);
        }
        else
        {
            processNext();
            msleep(mShortSleep);
        }
    }
}

void BaseCacheWorker::enqueueAll()
{
    Q_ASSERT(mUidQueue.isEmpty());
    mUidQueue.append(cache()->uidsInTouchOrder());
}

void BaseCacheWorker::processNext()
{
    if (cache()->count() < cache()->maxEntries()) // WANTDO BaseCacheWorker maxBytes
    {
        emit noneRemoved(cache(), cache()->count(), cache()->maxEntries());
        return;
    }
    bool removed = false;
    while ( ! mUidQueue.isEmpty() && ! removed)
    {
        const Uid cUid = mUidQueue.dequeue();
        emit dequeued(cache(), cUid);
        if (cache()->isHeld(cUid))
        {
            emit inUse(cache(), cUid);
        }
        else
        {
            cache()->remove(cUid);
            emit dequeued(cache(), cUid);
        }
    }
}
