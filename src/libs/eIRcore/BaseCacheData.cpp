#include "BaseCacheData.h"

class BaseClassDataData : public QSharedData
{
public:
};

BaseCacheData::BaseCacheData()
    : data(new BaseClassDataData)
{}

BaseCacheData::BaseCacheData(const BaseCacheData &rhs)
    : data{rhs.data}
{}

BaseCacheData &BaseCacheData::operator=(const BaseCacheData &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

BaseCacheData::~BaseCacheData() {}
