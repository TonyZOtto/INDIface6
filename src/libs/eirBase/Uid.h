#pragma once
#include "eIRbase.h"

#include <QUuid>

class EIRBASE_EXPORT Uid
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
