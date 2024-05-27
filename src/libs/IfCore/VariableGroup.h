#ifndef VARIABLEGROUP_H
#define VARIABLEGROUP_H
#include "IfCore.h"

#include <QtCore/QMap>
#include <QtCore/QString>

#include "Variable.h"
#include "VariableKey.h"
#include "VariableIdList.h"

class IFCORE_EXPORT VariableGroup
{
public:
    explicit VariableGroup(const VariableKey & sectionId=VariableKey());
    //VariableGroup(const QDomElement & de);
    VariableKey sectionId(void) const;
    bool isEmpty(void) const;
    int size(void) const;
    bool contains(const VariableKey & id) const;
    void add(const Variable & var);
    void add(VariableGroup * other,
             VariableKey sectionId=VariableKey());
    Variable at(const VariableKey & id) const;
    QVariant value(const VariableKey & id) const;
    bool set(const VariableKey & id, const Variable & var);
    bool set(const VariableKey & id, const QVariant & var);
    void set(const VariableGroup * vars);
    void reset(const VariableKey & id);
    void reset(void);
    void clear(void);
    void remove(const VariableKey & id);
    VariableIdList ids(void) const;
    QStringList sectionIds(const VariableKey & within=VariableKey());
    int implant(const VariableKey & sectionId,
                const VariableGroup * vars);
    QList<Variable> all(void) const;
    void dump(void) const;
    //QDomElement writeXml(void) const;
    //bool readXml(const QDomElement & de);
    int csvHeadingRowCount(void) const;

private:
    VariableKey section_id;
    QMap<QString, Variable> var_map;
    VariableIdList id_list;
    int csvRows;
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
