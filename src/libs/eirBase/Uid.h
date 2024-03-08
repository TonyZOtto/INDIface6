#pragma once

#include <QUuid>

class Uid
{
public:
    Uid(); // null
    Uid(const bool init); // random
    operator QUuid () const;

private:
    QUuid mUid;
};

inline Uid::operator QUuid() const
{
    return mUid;
}
