#include "Ident.h"

Ident::Ident(const Uid::Klass uk) { uid(Uid(uk)), id(0); }

Ident::Ident(const Uid::Klass uk, const Key k, const Id i, const QString d)
{
    uid(Uid(uk)), key(k), id(i), desc(d);
}

Ident::Ident(const Uid u, const Key k, const Id i, const QString d)
{
    uid(u), key(k), id(i), desc(d);
}
