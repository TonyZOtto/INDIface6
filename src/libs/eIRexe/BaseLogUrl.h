#pragma once

#include <QUrl>

#include <QString>

#include "Log.h"

class BaseLogUrl : public QUrl
{
public:

public: // ctors
    BaseLogUrl();
protected:
    BaseLogUrl(const Log::UrlType luty, const QString &s);

public:
    virtual Log::UrlType type() const = 0;

public:
    void set(const Log::UrlType luty);
    void set(const QString &url);

private:
    Log::UrlType mType=Log::$nullUrlType;
};
