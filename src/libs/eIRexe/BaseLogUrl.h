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
    BaseLogUrl(const Log::UrlType luty, const QUrl &url);

public:
    virtual Log::UrlType type() const = 0;

public:
    void set(const Log::UrlType luty);
    void set(const QString &s);
    void set(const QUrl &url);

protected:
    bool hasQuery(const QString &key) const;
    QString queryValue(const QString &key) const;
    QIODevice::OpenMode openMode() const;

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
