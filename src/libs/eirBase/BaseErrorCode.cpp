#include "BaseErrorCode.h"

#include <QFile>

BaseErrorCode::BaseErrorCode() : mUCode(0) {}
BaseErrorCode::BaseErrorCode(const unsigned int u) : mUCode(u) {;}
BaseErrorCode::BaseErrorCode(const Key key, const QString desc) : mUCode(0), mKey(key), mDescription(desc) {;}

BaseErrorCode::BaseErrorCode(QFile *pFile)
{
    Q_CHECK_PTR(pFile);
    if (mUCode = pFile->error())
    {
        mKey = "BaseErrorCode/FileError";
        mName = pFile->fileName();
        mDescription = QString("File error %1 [%2] in file %3")
                           .arg(pFile->errorString())
                           .arg(pFile->error())
                           .arg(mName);
    }
}

bool BaseErrorCode::isError() const
{
    bool result = false;
    if (mUCode)                     result = true;
    if (mKey.notNull())             result = true;
    if (mInstanceUid.notNull())     result = true;
    if ( ! mName.isEmpty())         result = true;
    if ( ! mDescription.isEmpty())  result = true;
    return result;
}

QString BaseErrorCode::toString() const
{
    QString result = isError() ? "BaseErrorString:" : "NoError";
    if (mUCode) result += " UCode=" + QString::number(mUCode);
    if (mKey.notNull()) result += " Key=" + mKey;
    if (mInstanceUid.notNull()) result += " Uid=" + mInstanceUid.tail();
    if ( ! mName.isEmpty()) result = " Name=" + mName;
    if ( ! mDescription.isEmpty()) result = " Description=" + mDescription;
    return result;
}


