#pragma once
#include "eIRbase.h"

#include <QMap>
#include <QVariant>

#include "Key.h"

class EIRBASE_EXPORT KeyMap
{
public: // ctors
    KeyMap();

public: // const
    bool contains(const Key &key) const;
    const QVariant value(const Key &key) const;
    const QVariant value(const Key &key, const QVariant &defalt) const;
    const Key::List keys() const;

public: // non-const
    void insert(const Key &key, const QVariant &var);
    void insert(const KeyMap &other, const Key &groupKey=Key());

private:
    QMap<Key, QVariant> mKeyVariantMap;
};

