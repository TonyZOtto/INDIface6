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

QStringList ObjectHelper::enumKeys(const QString &enumName) const
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

void ObjectHelper::dumpInfo() const
{
    object()->dumpObjectInfo();
    const QMetaObject * pMO = metaObject();
    qDebug() << "QMetaObject: Class Name =" << pMO->className() << object()->objectName();
    for (Index ix = pMO->classInfoOffset(); ix < pMO->classInfoCount(); ++ix)
        qDebug() << "   " << ix << pMO->classInfo(ix).name() << "=" << pMO->classInfo(ix).value();
    foreach (QString name, enumNames())
    {
        const QMetaEnum cME = metaEnum(name);
        if (cME.isValid())
        {
            qDebug() << object()->objectName() << "enum" << name;
            const Index cKeyCount = cME.keyCount();
            for (Index ix = 0; ix < cKeyCount; ++ix)
                qDebug() << "   " << ix << "=" << cME.key(ix);
        }
        else
        {
            qWarning() << "metaEnum(" << name << ") Invalid";
        }
    }
}
