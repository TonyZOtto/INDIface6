#include "VariableSet.h"

#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#include "VariableKeyList.h"

VariableSetData::VariableSetData(const VariableSetData & other)
    : QSharedData(other)
    , name_s(other.name_s)
    , key_u64(other.key_u64)
    , id_s(other.id_s)
    , vbl_map(other.vbl_map)
    , var_list(other.var_list)
    , _ba(other._ba)
{
}


VariableSet::VariableSet(const QString & name)
    : data(new VariableSetData)
{
    data->name_s = name;
}

VariableSet::VariableSet(const quint64 key,
            const QString & id,
            const QString & name)
    : data(new VariableSetData)
{
    data->name_s = name;
    data->key_u64 = key;
    data->id_s = id;
}

VariableSet::VariableSet(const VariableSet & other)
    : data(other.data)
{
}

VariableSet &VariableSet::operator=(const VariableSet & rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

VariableSet::~VariableSet()
{
}

QString VariableSet::name(void) const
{
    return data->name_s;
}

quint64 VariableSet::key(void) const
{
    return data->key_u64;
}

QString VariableSet::id(void) const
{
    return data->id_s;
}

void VariableSet::setName(const QString & newName)
{
    data->name_s = newName;
}

void VariableSet::setKey(const quint64 key)
{
    data->key_u64 = key;
}

void VariableSet::setId(const QString & id)
{
    data->id_s = id;
}

void VariableSet::clear(void)
{
    data->vbl_map.clear();
    data->var_list.clear();
    data->_ba.clear();
}

int VariableSet::binarySize(void) const
{
    return data->_ba.size();
}

int VariableSet::listSize(void) const
{
    return data->var_list.size();
}

int VariableSet::mapSize(void) const
{
    return data->vbl_map.size();
}

bool VariableSet::contains(const VariableKey &key) const
{
    return data->vbl_map.contains(key.sortable());
}

void VariableSet::reset(void)
{
    foreach (QString key, data->vbl_map.keys())
        data->vbl_map[key].reset();
}

bool VariableSet::isEmpty(void) const
{
    return data->vbl_map.isEmpty()
                && data->var_list.isEmpty()
                && data->_ba.isEmpty();
}

void VariableSet::set(const QVariantList & vl)
{
    data->var_list = vl;
}

void VariableSet::set(const Variable & var)
{
    //data->vbl_map.insert(vbl.id().sortable(), vbl);
    data->vbl_map[var.key().sortable()] = var;
}

void VariableSet::set(const VariableKey &key, const QVariant & value)
{
    //data->vbl_map.insert(vid.sortable(), Variable(vid, value));
    QVariant def(data->vbl_map[key.sortable()].defaultVar());
    data->vbl_map[key.sortable()] = Variable(key, value, def);
}

void VariableSet::set(const int index, const QVariant & value)
{
    while (data->var_list.size() <= index)
        data->var_list.append(QVariant());
    data->var_list[index] = value;
}

void VariableSet::set(const QByteArray & ba)
{
    data->_ba = ba;
}

void VariableSet::reset(const VariableKey &key)
{
    if (data->vbl_map.contains(key.sortable()))
        data->vbl_map[key.sortable()].reset();
}

void VariableSet::append(const QVariant & value)
{
    data->var_list.append(value);
}

Variable VariableSet::at(const VariableKey & key) const
{
    return data->vbl_map.value(key.sortable());
}

QVariant VariableSet::value(const VariableKey &key,
                            const QVariant &defaultValue) const
{
#if 1 // def QT_DEBUG
    QString skey(key.sortable());
    if (data->vbl_map.contains(skey))
    {
        Variable vbl(data->vbl_map.value(skey));
        QVariant var(vbl.var());
        return var;
    }
    else
        return defaultValue;
#else
    return data->vbl_map.value(id.sortable()).var();
#endif
}

QVariant VariableSet::value(const int index) const
{
    return (index >= 0 && index < data->var_list.size())
            ? data->var_list.at(index)
            : QVariant();
}

QByteArray VariableSet::value(void) const
{
    return data->_ba;
}

QVariantList VariableSet::values(void) const
{
    return data->var_list;
}


VariableSet VariableSet::exportSection(const VariableKey &sectionKey) const
{
    VariableSet result;
    int n = sectionKey.count();
    foreach (VariableKey key, keys(sectionKey))
    {
            VariableKey newId(key.segment(n));
            result.set(newId, value(key));
    }
    return result;
}

VariableKeyList VariableSet::keys(const VariableKey &within) const
{
    VariableKeyList result;
    if (within.isNull())
        foreach (Variable var, data->vbl_map.values())
            result.append(var.key());
    else
    {
        QString prefix(within.sortable());
        foreach (Variable vbl, data->vbl_map.values())
            if (vbl.key().sortable().startsWith(prefix))
                result.append(vbl.key());
    }
    return result;
}

VariableKeyList VariableSet::sectionIds(const VariableKey &within) const
{
    VariableKeyList result;
    if (within.isNull())
        foreach (Variable vbl, data->vbl_map.values())
        {
            QString section(vbl.key().segment(0));
            if ( ! result.contains(VariableKey(section)))
                result.append(VariableKey(section));
        }
    else
    {
        int n = within.count();
        foreach (Variable vbl, data->vbl_map.values())
        {
            QString section(vbl.key().segment(n));
            if (within.toString() == Key(vbl.key().segments(0, n-1)).toString())
                if ( ! result.contains(VariableKey(section)))
                    result.append(VariableKey(section));
        }
    }
    return result;
}

void VariableSet::import(const VariableSet & other,
                         const VariableKey &sectionId)
{
    foreach (Variable var, other.data->vbl_map.values())
    {
        VariableKey key(var.key());
        key.prepend(sectionId);
        set(key, var.var());
    }
}

QList<Variable> VariableSet::all(void) const
{
    return data->vbl_map.values();
}
