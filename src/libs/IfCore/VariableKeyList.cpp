#include "VariableKeyList.h"

VariableKeyList::VariableKeyList(void)
{
}

VariableKeyList::operator QStringList(void) const
{
    QStringList result;
    int x = 0;
    while (x < size())
        result << at(x++).toString();
    return result;
}
