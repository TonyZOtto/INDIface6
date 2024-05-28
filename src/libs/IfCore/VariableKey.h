#ifndef VARIABLEID_H
#define VARIABLEID_H
#include "IfCore.h"

#include <QString>

//#include <Key.h>
#include "../eIRbase/Key.h"
#include "../eIRbase/KeySeg.h"

class IFCORE_EXPORT VariableKey : public Key
{
public:
    VariableKey(const QString & inString=QString());
    VariableKey(const KeySeg & seg);
    VariableKey(const KeySeg::List & segs);
    VariableKey(const char * chars);
    VariableKey(const char * chars,
               const char * chars1,
               const char * chars2=0,
               const char * chars3=0);
    VariableKey(const VariableKey & prefix,
               const char * suffix);
};

extern IFCORE_EXPORT bool operator == (const VariableKey &lhs, const VariableKey &rhs);

#endif // VARIABLEID_H
