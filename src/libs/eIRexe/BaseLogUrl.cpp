#include "BaseLogUrl.h"

BaseLogUrl::BaseLogUrl() { set($null); }

BaseLogUrl::BaseLogUrl(const Type t, const QString &s)
{
    set(t); set(s);
}


void BaseLogUrl::set(const Type t)
{
    mType = t;
}

void BaseLogUrl::set(const QString &s)
{
    QUrl::setUrl(s);
}

