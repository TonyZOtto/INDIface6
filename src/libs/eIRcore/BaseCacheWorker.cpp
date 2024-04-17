#include "BaseCacheWorker.h"

#include "BaseUidCache.h"

BaseCacheWorker::BaseCacheWorker(BaseUidCache *parent)
    : QThread{parent}
    , cmpCache(parent)
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
    Q_ASSERT(!"MUSSTDO"); // MUSTDO enqueueAll()
}

void BaseCacheWorker::processNext()
{
    Q_ASSERT(!"MUSSTDO"); // MUSTDO processNext()
}
