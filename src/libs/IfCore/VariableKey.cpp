#include "VariableKey.h"
#include "../eirBase/BaseIdBehavior.h"
#if 0
    VariableIdBehavior(void)
        : BaseIdBehavior("/", "/" + lower + upper + number)
    {
        replace("_", "/");
    }

    static VariableIdBehavior * singleton;
#endif
VariableKey::VariableKey(const char * chars,
                       const char * chars1,
                       const char * chars2,
                       const char * chars3)
    : Key(VariableIdBehavior::instance())
{
    set(QString(chars));
    append(QString(chars1));
    append(QString(chars2));
    append(QString(chars3));
}

VariableKey::VariableKey(const VariableKey & prefix,
                       const char * suffix)
    : Key(VariableIdBehavior::instance(),
                       prefix)
{
    append(QString(suffix));
}
