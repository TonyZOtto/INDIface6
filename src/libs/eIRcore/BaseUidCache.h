#pragma once
#include "eIRcore.h"

#include <QObject>

#include <QMap>
#include <QMultiMap>

#include "../eIRbase/Types.h"
#include "../eIRbase/Uid.h"
#include "../eIRcore/DualMap.h"
#include "BaseCacheEntry.h"
class BaseCacheWorker;

class EIRCORE_EXPORT BaseUidCache : public QObject
{
    Q_OBJECT
public:
    explicit BaseUidCache(QObject *parent = nullptr);

public: // const
    bool contains(const Uid uid) const;
    Count count() const;
    bool isHeld(const Uid uid) const;
    BaseCacheEntry read(const Uid uid) const;
    Uid::List uidsInTouchOrder() const;

public: // non-const
    Uid add(const BaseCacheEntry &entry);
    void write(const Uid uid, const BaseCacheEntry &entry);
    void touch(const Uid entryUid);
    void hold(const Uid entryUid, void * holder);
    void release(const Uid entryUid, void * holder);
    void remove(const Uid uid);

public: // pointers
    const BaseCacheWorker *worker();

public slots:

private:
    const BaseCacheWorker * cmpWorker=nullptr;
    QMap<Uid, BaseCacheEntry> mUidEntryMap;
    DualMap<Uid, Key> mUidKeyDMap;
    QMultiMap<EpochMilliseconds, Uid> mTouchEmsUidMap;

    // ------------------------ Properties --------------------------
private:
    Count m_maxEntries=256;
    Count m_maxBytes=1024 * 1024;
    Q_PROPERTY(Count maxEntries READ maxEntries WRITE maxEntries NOTIFY changed_maxEntries FINAL)
    Q_PROPERTY(Count maxBytes READ maxBytes WRITE maxBytes NOTIFY changed_maxBytes FINAL)
public:
    Count maxEntries() const;
    void maxEntries(Count new_maxEntries);
    Count maxBytes() const;
    void maxBytes(Count new_maxBytes);
signals:
    void changed_maxEntries();
    void changed_maxBytes();
};

inline const BaseCacheWorker *BaseUidCache::worker()
{
    return cmpWorker;
}

inline Count BaseUidCache::maxEntries() const
{
    return m_maxEntries;
}

inline void BaseUidCache::maxEntries(Count new_maxEntries)
{
    if (m_maxEntries == new_maxEntries)
        return;
    m_maxEntries = new_maxEntries;
    emit changed_maxEntries();
}

inline Count BaseUidCache::maxBytes() const
{
    return m_maxBytes;
}

inline void BaseUidCache::maxBytes(Count new_maxBytes)
{
    if (m_maxBytes == new_maxBytes)
        return;
    m_maxBytes = new_maxBytes;
    emit changed_maxBytes();
}
