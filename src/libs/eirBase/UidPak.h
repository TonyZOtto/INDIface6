#pragma once

#include <QMap>

#include "Key.h"
#include "Uid.h"

class UidPak
{
public: // ctors
    UidPak();

public: // const
    Key key(const Uid uid) const;
    Uid uid(const Key &key) const;
    bool contains(const Uid uid) const;
    bool contains(const Key &key) const;

public: // non-const
    Uid add(const Key &key);
    void add(const Uid uid, const Key &key);

private:
    QMap<Uid, Key> mUidKeyMap;
    QMap<Key, Uid> mKeyUidMap;
};
