#ifndef VARIABLEKEYLIST_H
#define VARIABLEKEYLIST_H
#include "IfCore.h"

#include <QtCore/QList>
#include "VariableKey.h"


class IFCORE_EXPORT VariableKeyList : public QList<VariableKey>
{
public:
    VariableKeyList(void);

    operator QStringList(void) const;

};

#endif // VARIABLEKEYLIST_H
