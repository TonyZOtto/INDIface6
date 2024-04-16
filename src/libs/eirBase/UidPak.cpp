#include "UidPak.h"

UidPak::UidPak() {}

Key UidPak::key(const Uid uid) const
{
    Key result;
    if (mUidKeyMap.contains(uid)) result = mUidKeyMap[uid];
#ifdef QT_DEBUG
    if (result.notNull())
    {
        Q_ASSERT(mKeyUidMap.contains(result));
        //Q_ASSERT(mKeyUidMap.value(result) == uid);
    }
#endif
    return result;
}
