#ifndef VARIABLEID_H
#define VARIABLEID_H
#include "IfCore.h"

#include <Key.h>

class IFCORE_EXPORT VariableKey : public Key
{
public:
    VariableKey(const QString & inString=QString());
    VariableKey(const char * chars);
    VariableKey(const char * chars,
               const char * chars1,
               const char * chars2=0,
               const char * chars3=0);
    VariableKey(const VariableKey & prefix,
               const char * suffix);
};

#endif // VARIABLEID_H
