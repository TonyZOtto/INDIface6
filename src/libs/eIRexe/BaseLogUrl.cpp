#include "BaseLogUrl.h"

BaseLogUrl::BaseLogUrl() { set(Log::$nullUrlType); }

BaseLogUrl::BaseLogUrl(const Log::UrlType luty, const QString &url)
{
    set(luty); set(url);
}


void BaseLogUrl::set(const Log::UrlType luty)
{
    mType = luty;
}

void BaseLogUrl::set(const QString &url)
{
    QUrl::setUrl(url);
}

