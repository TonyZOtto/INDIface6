#include "ObjectHelper.h"

#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>

#include "../eIRbase/Types.h"

ObjectHelper::ObjectHelper() : mpObject(nullptr) {;}
ObjectHelper::ObjectHelper(QObject * opb) : mpObject(opb) {;}

QMetaEnum ObjectHelper::metaEnum(const KeySeg &enumName) const
{
    const QMetaObject * pMO = metaObject();
    for (Index ix = pMO->enumeratorOffset(); ix < pMO->enumeratorCount(); ++ix)
    {
        QMetaEnum tME = pMO->enumerator(ix);
        if (tME.name() == enumName)
            return tME;
    }
    return QMetaEnum();
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
