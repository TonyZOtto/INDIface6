#pragma once

#include <QThread>

#include <QQueue>

#include "../eIRbase/Types.h"
#include "../eIRbase/Uid.h"
class BaseUidCache;

class BaseCacheWorker : public QThread
{
    Q_OBJECT
public:
    explicit BaseCacheWorker(BaseUidCache *parent = nullptr);

public:
    void shutdown();

signals:
    void dequeued(const BaseUidCache * cache, const Uid uid);
    void inUse(const BaseUidCache * cache, const Uid uid);
    void noneRemoved(const BaseUidCache * cache, const Count cachedCount, const Count maxCount);

private:
    void run() override;
    void enqueueAll();
    void processNext();
    BaseUidCache *cache();

private:
    BaseUidCache * mpCache=nullptr;
    bool mShutdown=false;
    EpochMilliseconds mShortSleep=100;
    EpochMilliseconds mLongSleep=5000;
    QQueue<Uid> mUidQueue;
};

inline BaseUidCache *BaseCacheWorker::cache()
{
    Q_CHECK_PTR(mpCache);
    return mpCache;
}
