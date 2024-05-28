#include "VariableKey.h"

VariableKey::VariableKey(const char * chars, const char * chars1,
                       const char * chars2, const char * chars3)
    : Key(chars, chars1, chars2, chars3) {;}

VariableKey::VariableKey(const QString &inString) : Key(inString) {;}

VariableKey::VariableKey(const KeySeg &seg) : Key(seg) {;}

VariableKey::VariableKey(const KeySeg::List &segs) : Key(segs) {;}

VariableKey::VariableKey(const char *chars) : Key(chars) {;}

VariableKey::VariableKey(const VariableKey & prefix,
                       const char * suffix)
    : Key(prefix.toString())
{
    append(QString(suffix));
    if (contains('_')) Q_ASSERT("!MUSTDO:replace");
}

bool operator == (const VariableKey &lhs, const VariableKey &rhs)
{
    return lhs.sortable() == rhs.sortable();
}
