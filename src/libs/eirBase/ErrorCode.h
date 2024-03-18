#pragma once

#include <QString>

#include "Key.h"
#include "Uid.h"

class BaseErrorCode
{
public:
    BaseErrorCode();
    BaseErrorCode(const unsigned u);
    BaseErrorCode(const Key key);


private:
    unsigned mUCode;
    Key mKey;
    Uid mInstanceUid;
    QString mName;
    QString mDescription;
};
