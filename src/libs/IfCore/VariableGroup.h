#ifndef VARIABLEGROUP_H
#define VARIABLEGROUP_H
#include "IfCore.h"

#include <QtCore/QMap>
#include <QtCore/QString>

#include "Variable.h"
#include "VariableKey.h"
#include "VariableKeyList.h"

class IFCORE_EXPORT VariableGroup
{
public:
    explicit VariableGroup(const VariableKey & sectionKey=VariableKey());
    //VariableGroup(const QDomElement & de);
    VariableKey sectionKey(void) const;
    bool isEmpty(void) const;
    int size(void) const;
    bool contains(const VariableKey & key) const;
    void add(const Variable & var);
    void add(VariableGroup * other,
             VariableKey sectionId=VariableKey());
    Variable at(const VariableKey & id) const;
    QVariant value(const VariableKey & key) const;
    bool set(const VariableKey & id, const Variable & var);
    bool set(const VariableKey & key, const QVariant & var);
    void set(const VariableGroup * vars);
    void reset(const VariableKey & key);
    void reset(void);
    void clear(void);
    void remove(const VariableKey & key);
    VariableKeyList keys(void) const;
    QStringList sectionKeys(const VariableKey & within=VariableKey());
    int implant(const VariableKey & sectionKey,
                const VariableGroup * vars);
    QList<Variable> all(void) const;
    void dump(void) const;
    int csvHeadingRowCount(void) const;

private:
    VariableKey mSectionKey;
    QMap<QString, Variable> mKeyVarMap;
    VariableKeyList mKeyList;
    int mCsvCount;
};

#define GROUPVARIABLES_DECLARE(ID, TYPE, DFLT) \
        void reset##ID(void) { reset(VariableId(#ID)); } \
        TYPE get##ID(void) const { return value(VariableId(#ID)).value<TYPE>(); } \
        void set##ID(TYPE v) { set(VariableId(#ID), QVariant(v)); } \

#define GROUPVARIABLES_CTOR(ID, TYPE, DFLT) \
        VariableGroup::add(Variable(VariableId(#ID), QVariant((TYPE)DFLT))); \

#define DECLARE_GROUPVARIABLES(DEF) \
        DEF(GROUPVARIABLES_DECLARE) \

#define DEFINE_GROUPVARIABLES_CTORS(DEF) \
        DEF(GROUPVARIABLES_CTOR) \

#endif // VARIABLEGROUP_H
