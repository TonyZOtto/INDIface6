#include "BaseErrorCode.h"

BaseErrorCode::BaseErrorCode() : mUCode(0) {}
BaseErrorCode::BaseErrorCode(const unsigned int u) : mUCode(u) {;}
BaseErrorCode::BaseErrorCode(const Key key, const QString desc) : mUCode(0), mKey(key), mDescription(desc) {;}

bool BaseErrorCode::isError() const
{
    bool result = false;
    if (mUCode)                     result = true;
    if (mKey.notNull())             result = true;
    if (mInstanceUid.notNull())     result = true;
    if ( ! mName.isNull())          result = true;
    if ( ! mDescription.isNull())   result = true;
    return result;
}


