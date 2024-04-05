#include "ObjectHelper.h"

#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>
#include <QString>

#include "../eIRbase/Types.h"

ObjectHelper::ObjectHelper() : mpObject(nullptr) {;}
ObjectHelper::ObjectHelper(QObject * opb) : mpObject(opb) {;}

QMetaEnum ObjectHelper::metaEnum(const KeySeg &enumName) const
{
    QMetaEnum result;
    const QMetaObject * pMO = metaObject();
    for (Index ix = pMO->enumeratorOffset(); ix < pMO->enumeratorCount(); ++ix)
    {
        QMetaEnum tME = pMO->enumerator(ix);
        if (tME.name() == enumName)
        {
            result = tME;
            break;
        }
    }
    return result;
}

QStringList ObjectHelper::enumNames(const bool all) const
{
    //qInfo() << Q_FUNC_INFO << all;
    QStringList result;
    const QMetaObject * pMO = metaObject();
    for (Index ix = all ? 0 :pMO->enumeratorOffset(); ix < pMO->enumeratorCount(); ++ix)
    {
        QMetaEnum tME = pMO->enumerator(ix);
        const QString cStr(tME.name());
        result << cStr;
        //qDebug() << tME.name() << cStr << result;
    }
    return result;
}

QStringList ObjectHelper::enumKeys(const KeySeg &enumName) const
{
    QStringList result;
    const QMetaEnum cME = metaEnum(enumName);
    qInfo() << Q_FUNC_INFO << enumName << cME.isValid() << cME.keyCount();
    if (cME.isValid())
    {
        const Index cKeyCount = cME.keyCount();
        for (Index ix = 0; ix < cKeyCount; ++ix)
            result << cME.key(ix);
    }
    return result;
}

int ObjectHelper::flagRange(const KeySeg &enumName,
                            const KeySeg &fromValueName,
                            const KeySeg &toValueName) const
{
    int result = 0;
    const QMetaEnum cME = metaEnum(enumName);
    if (cME.isValid())
    {
        const int cBeg = cME.keyToValue(fromValueName);
        const int cEnd = cME.keyToValue(toValueName);
        if (cBeg > 0 && cEnd >= cBeg)
            for (Index ix = cBeg; ix < cEnd; ++ix)
                result |= 1 << ix;
    }
    return result;
}

const QMetaObject *ObjectHelper::metaObject() const
{
    return object()->metaObject();
}
