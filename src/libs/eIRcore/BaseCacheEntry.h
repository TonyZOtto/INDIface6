#pragma once

#include <QObject>

#include <QList>
#include <QVariant>

#include "../eIRbase/Ident.h"
#include "../eIRbase/Key.h"
#include "../eIRbase/KeyMap.h"
#include "../eIRbase/Types.h"
#include "../eIRbase/Uid.h"

class BaseCacheEntry
{
    Q_GADGET
public: // ctors
    BaseCacheEntry();
    BaseCacheEntry(const Key &entryKey, const Id id=0);

public: // const
    Ident ident() const;
    bool contains(const Key &valueKey) const;
    QVariant read(const Key &valueKey) const;
    EpochMilliseconds lastTouch() const;

public: // non-const
    void set(const Ident &i);
    void hold(void *holder);
    void release(void * holder);
    void touch();
    void write(const Key &valueKey, const QVariant &value);

private:
    Ident mIdent;
    EpochMilliseconds mLastTouchEms;
    QList<void *> mHolderList;
    KeyMap mKeyMap;
};

inline Ident BaseCacheEntry::ident() const
{
    return mIdent;
}

inline EpochMilliseconds BaseCacheEntry::lastTouch() const
{
    return mLastTouchEms;
}

