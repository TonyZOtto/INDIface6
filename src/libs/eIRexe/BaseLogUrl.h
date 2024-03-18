#pragma once

#include <QUrl>

#include <QIODevice>
#include <QString>
#include <QUrlQuery>

#include "LogObject.h"

class BaseLogUrl : public QUrl
{
public:

public: // ctors
    BaseLogUrl();
protected:
    BaseLogUrl(const Log::UrlType luty, const QString &s);

public:
    virtual Log::UrlType type() const = 0;
    bool hasQuery(const QString &key) const;
    QString queryValue(const QString &key) const;
    QIODevice::OpenMode openMode() const;

public:
    void set(const Log::UrlType luty);
    void set(const QString &url);

private:
    void parseOpenMode();

private:
    Log::UrlType mType=Log::$nullUrlType;
    QUrlQuery mQuery;
    QIODevice::OpenMode mOpenMode=QIODevice::NotOpen;
};

inline QIODeviceBase::OpenMode BaseLogUrl::openMode() const
{
    return mOpenMode;
}
