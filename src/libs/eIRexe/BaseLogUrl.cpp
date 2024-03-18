#include "BaseLogUrl.h"

#include <QStringList>

#include "../eIRcore/IODevice.h"

BaseLogUrl::BaseLogUrl() { set(Log::$nullUrlType); }

BaseLogUrl::BaseLogUrl(const Log::UrlType luty, const QString &url)
{
    set(luty); set(url);
}

bool BaseLogUrl::hasQuery(const QString &key) const
{
    return mQuery.hasQueryItem(key);
}

QString BaseLogUrl::queryValue(const QString &key) const
{
    return mQuery.queryItemValue(key);
}

void BaseLogUrl::set(const Log::UrlType luty)
{
    mType = luty;
}

void BaseLogUrl::set(const QString &url)
{
    QUrl::setUrl(url);
    mQuery = QUrlQuery(*this);
    parseOpenMode();
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

