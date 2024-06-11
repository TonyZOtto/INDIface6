#include "BaseLogUrl.h"

#include <QStringList>

#include "../eIRcore/IODevice.h"

#include "LogObject.h"

BaseLogUrl::BaseLogUrl() { set(Log::$nullUrlType); }

BaseLogUrl::BaseLogUrl(const Log::UrlType luty, const QString &s)
{
    set(luty); set(s);
}

BaseLogUrl::BaseLogUrl(const Log::UrlType luty, const QUrl &url)
{
    set(luty); set(url);
}

void BaseLogUrl::set(const Log::UrlType luty)
{
    mType = luty;
}

void BaseLogUrl::set(const QString &s)
{
    QUrl::setUrl(s);
    mQuery = QUrlQuery(*this);
    parseOpenMode();
}

void BaseLogUrl::set(const QUrl &url)
{
    QUrl::setUrl(url.toString());
    mQuery = QUrlQuery(*this);
    parseOpenMode();
}

bool BaseLogUrl::hasQuery(const QString &key) const
{
    return mQuery.hasQueryItem(key);
}

QString BaseLogUrl::queryValue(const QString &key) const
{
    return mQuery.queryItemValue(key);
}


void BaseLogUrl::parseOpenMode()
{
    mOpenMode = QIODevice::NotOpen;
    if (hasQuery("OpenMode"))
    {
        const QStringList tOMValues = queryValue("OpenMode").split("+");
        mOpenMode = IODevice::openMode(tOMValues);
    }
}


