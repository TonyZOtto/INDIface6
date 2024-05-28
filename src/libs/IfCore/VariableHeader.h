#ifndef VARIABLEHEADER_H
#define VARIABLEHEADER_H
#include "IfCore.h"

#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QPair>

#include "VariableKey.h"
class VariableGroup;
class VariableType;

typedef QPair<VariableKey, VariableType *> VariableColumn;

class IFCORE_EXPORT VariableHeader
{
public:
    VariableHeader(void);
    VariableHeader(VariableGroup * vg);
    bool isNull(void) const;
    int size(void) const;
    VariableKey key(int index) const;
    QMetaType::Type metaType(int index) const;
    QList<VariableColumn> header(void) const;

private:
    QList<VariableColumn> column_list;
};

#endif // VARIABLEHEADER_H
