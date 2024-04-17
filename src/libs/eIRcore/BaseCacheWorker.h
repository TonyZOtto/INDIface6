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


private:
    void run() override;
    void enqueueAll();
    void processNext();
    const BaseUidCache *cache();

private:
    const BaseUidCache * cmpCache=nullptr;
    bool mShutdown=false;
    EpochMilliseconds mShortSleep=100;
    EpochMilliseconds mLongSleep=5000;
    QQueue<Uid> mUidQueue;
};

inline const BaseUidCache *BaseCacheWorker::cache()
{
    return cmpCache;
}
