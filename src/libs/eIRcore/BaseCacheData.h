#pragma once

#include <QSharedDataPointer>

class BaseClassDataData;

class BaseCacheData
{
public:
    BaseCacheData();
    BaseCacheData(const BaseCacheData &);
    BaseCacheData &operator=(const BaseCacheData &);
    ~BaseCacheData();

private:
    QSharedDataPointer<BaseClassDataData> data;
};
