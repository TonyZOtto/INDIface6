#pragma once

#include <QUrl>

#include <QString>

class BaseLogUrl : public QUrl
{
public:
    enum Type { $null = 0, Cache, Output };

public: // ctors
    BaseLogUrl();
protected:
    BaseLogUrl(const Type t, const QString &s);

public:
    virtual Type type() const = 0;

public:
    void set(const Type t);
    void set(const QString &s);

private:
    Type mType=$null;
};
