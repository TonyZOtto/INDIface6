#ifndef VARIABLEIDLIST_H
#define VARIABLEIDLIST_H
#include "IfCore.h"

#include <QtCore/QList>
#include "VariableKey.h"


class IFCORE_EXPORT VariableIdList : public QList<VariableKey>
{
public:
    VariableIdList(void);

    operator QStringList(void) const;

};

#endif // VARIABLEIDLIST_H
