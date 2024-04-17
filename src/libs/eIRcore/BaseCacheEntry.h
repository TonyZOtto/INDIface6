#pragma once

#include <QObject>

#include <QList>
#include <QVariant>

#include "../eIRbase/Key.h"
#include "../eIRbase/KeyMap.h"
#include "../eIRbase/Types.h"
#include "../eIRbase/Uid.h"

class BaseCacheEntry
{
    Q_GADGET
public: // ctors
    BaseCacheEntry();
    BaseCacheEntry(const Key &key, const Id id=0);


public: // const
    bool contains(const Key &key) const;
    QVariant read(const Key &key) const;

public: // non-const
    void set(const Uid uid);
    void set(const Key &key, const Id id=0);
    void hold(const void * holder);
    void release(const void * holder);
    void touch(const void * holder);
    void write(const Key &key, const QVariant &value);

private:
    EpochMilliseconds mLastTouchEms;
    QList<void *> mHoldersList;
    KeyMap mKeyMap;

    // ---------------------- Properties -------------------------
public:
    Uid uid() const;
    Key key() const;
    Id id() const;
private:
    Uid     p_uid;
    Key     p_key;
    Id      p_id;
    Q_PROPERTY(Uid uid READ uid CONSTANT FINAL)
    Q_PROPERTY(Key key READ key CONSTANT FINAL)
    Q_PROPERTY(Id id READ id CONSTANT FINAL)
};

inline Uid BaseCacheEntry::uid() const
{
    return p_uid;
}

inline Key BaseCacheEntry::key() const
{
    return p_key;
}

inline Id BaseCacheEntry::id() const
{
    return p_id;
}
