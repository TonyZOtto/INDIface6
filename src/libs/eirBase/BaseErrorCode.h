#pragma once
#include "eirBase.h"

#include <QString>
class QFile;

#include "Key.h"
#include "Uid.h"

class EIRBASE_EXPORT BaseErrorCode
{
public:
    BaseErrorCode();
    BaseErrorCode(const unsigned u);
    BaseErrorCode(const Key key, const QString desc=QString());
    BaseErrorCode(QFile * pFile);

public:
    bool isError() const;
    bool notError() const { return ! isError(); }
    QString toString() const;
    operator bool () const { return isError(); }

private:
    unsigned mUCode;
    Key mKey;
    Uid mInstanceUid;
    QString mName;
    QString mDescription;
};
