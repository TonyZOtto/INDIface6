#pragma once
#include "eIRcore.h"

#include <QObject>

#include <QList>
#include <QVariant>

#include "../eIRbase/Ident.h"
#include "../eIRbase/Key.h"
#include "../eIRbase/KeyMap.h"
#include "../eIRbase/Types.h"
#include "../eIRbase/Uid.h"

class EIRCORE_EXPORT BaseCacheEntry
{
    Q_GADGET
public: // ctors
    BaseCacheEntry();
    BaseCacheEntry(const Key &entryKey, const Id id=0);

public: // const
    Uid uid() const;
    Ident ident() const;
    QVariant data() const;
    KeyMap map() const;
    bool contains(const Key &valueKey) const;
    bool isHeld() const;
    QVariant get(const Key &valueKey) const;
    EpochMilliseconds lastTouch() const;

public: // non-const
    void uid(const Uid aUid);
    void ident(const Ident &i);
    void data(const QVariant &km);
    void map(const KeyMap &km);
    void hold(void *holder);
    void release(void * holder);
    void touch();
    void set(const Key &valueKey, const QVariant &value);

private:
    Ident mIdent;
    EpochMilliseconds mLastTouchEms;
    QList<void *> mHolderList;
    QVariant mData;
    KeyMap mKeyMap;
};

inline Ident BaseCacheEntry::ident() const { return mIdent; }
inline EpochMilliseconds BaseCacheEntry::lastTouch() const { return mLastTouchEms; }
inline void BaseCacheEntry::ident(const Ident &i) { mIdent = i;}
inline void BaseCacheEntry::map(const KeyMap &km) { mKeyMap = km; }

