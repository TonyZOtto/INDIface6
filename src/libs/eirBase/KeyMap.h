#pragma once
#include "eIRbase.h"

#include <QMap>
#include <QVariant>

#include "Ident.h"
#include "Key.h"

class EIRBASE_EXPORT KeyMap
{
public: // ctors
    KeyMap();
    KeyMap(const Ident aIdent);
    KeyMap(const Key aKey);

public: // const
    Ident ident() const;
    bool contains(const Key &key) const;
    QVariant get(const Key &aKey) const;
    QVariant get(const Key &aKey, const QVariant &aDefault) const;
    const QVariant value(const Key &aKey) const;
    const QVariant value(const Key &aKey, const QVariant &aDefault) const;
    const Key::List keys() const;

public: // non-const
    void insert(const Key &key, const QVariant &var);
    void insert(const KeyMap &other, const Key &groupKey=Key());

private:
    Ident mIdent;
    QMap<Key, QVariant> mKeyVariantMap;
};

inline Ident KeyMap::ident() const { return mIdent; }
