#include "VariableGroup.h"

#include <QtDebug>
#include <QtXml/QDomElement>

VariableGroup::VariableGroup(const VariableKey &sectionKey) : mSectionKey(sectionKey) {;}

VariableKey VariableGroup::sectionKey(void) const
{
    return mSectionKey;
}

bool VariableGroup::isEmpty(void) const
{
    return mKeyVarMap.isEmpty();
}

int VariableGroup::size(void) const
{
    return mKeyVarMap.size();
}

bool VariableGroup::contains(const VariableKey & key) const
{
    return mKeyVarMap.contains(key.sortable());
}

void VariableGroup::add(const Variable & var)
{
    VariableKey key = var.key();
    key.prepend(mSectionKey);
    mKeyList.append(key);
    mKeyVarMap.insert(key.sortable(), var);
    //qDebug() << objectName() << vid() << "<+" << var.var();
    mCsvCount = qMax(mCsvCount, var.csvHeadingCount());
}

void VariableGroup::add(VariableGroup * other,
                        VariableKey sectionKey)
{
    if (sectionKey.isNull()) sectionKey = other->sectionKey();
    foreach (Variable var, other->all())
    {
        VariableKey key(var.key());
        key.prepend(sectionKey);
        set(key, var.var());
    }
}

Variable VariableGroup::at(const VariableKey & key) const
{
    Variable v(mKeyVarMap.value(key.sortable()));
    return v;
}

QVariant VariableGroup::value(const VariableKey & key) const
{
    return at(key).var();
}

bool VariableGroup::set(const VariableKey & key, const Variable & var)
{
    bool result = mKeyVarMap.contains(key.sortable());
    if (result)
        mKeyVarMap[key.sortable()] = var;
    else
        add(var);
    //qDebug() << objectName() << id() << "<-" << var.var();
    return result;
}

bool VariableGroup::set(const VariableKey & key, const QVariant & var)
{
    if (mKeyVarMap.contains(key.sortable()))
    {
        mKeyVarMap[key.sortable()].set(var);
        //qDebug() << sectionId()() << id() << "<-" << var;
        return true;
    }
    else
    {
        add(Variable(key, var));
        return false;
    }
}

void VariableGroup::set(const VariableGroup * vars)
{
    foreach (Variable v, vars->all())
        set(v.key(), v);
}

int VariableGroup::implant(const VariableKey & sectionKey,
                           const VariableGroup * vars)
{
    int count = 0;
    foreach (Variable v, vars->all())
        if (v.key().segment(0)() == sectionKey.toString())
        {
            VariableKey key = v.key();
            QString newKey = Key(key.segments(1)).toString();
            //qDebug() << newId << "<i" << v.var();
            set(VariableKey(newKey), v.var());
            ++count;
        }
    return count;
}

void VariableGroup::reset(const VariableKey & key)
{
    if (mKeyVarMap.contains(key.sortable()))
        mKeyVarMap[key.sortable()].reset();
}

void VariableGroup::reset()
{
    foreach (QString key, mKeyVarMap.keys())
        mKeyVarMap[key].reset();
}

void VariableGroup::clear(void)
{
    mKeyVarMap.clear();
    mKeyList.clear();
}

void VariableGroup::remove(const VariableKey & key)
{
    mKeyVarMap.remove(key.sortable());
    mKeyList.removeAll(key);
}

VariableKeyList VariableGroup::keys(void) const
{
    return mKeyList;
}

QStringList VariableGroup::sectionKeys(const VariableKey & within)
{
    QStringList result;

    if (within.isNull())
        foreach (VariableKey key, mKeyList)
        {
            QString section(key.segment(0));
            if ( ! result.contains(section))
                result.append(section);
        }
    else
    {
        int n = within.count();
        foreach (VariableKey key, mKeyList)
        {
            QString section(key.segment(n));
            if (QString(within) == Key(key.segments(0, n-1)).toString())
                if ( ! result.contains(section))
                    result.append(section);
        }
    }

    return result;
}

QList<Variable> VariableGroup::all(void) const
{
    return mKeyVarMap.values();
}

void VariableGroup::dump(void) const
{
    qDebug() << "Dumping" << sectionKey();
    foreach (VariableKey key, mKeyList)
    {
        Variable v = mKeyVarMap.value(key.sortable());
        qDebug() << "---" << key << "=" << v.var();
    }
}

int VariableGroup::csvHeadingRowCount(void) const
{
    return mCsvCount;
}
