#pragma once
#include "eIRcore.h"

class QObject;

#include <QStringList>

#include "../eIRbase/KeySeg.h"

class EIRCORE_EXPORT ObjectHelper
{
public:
    ObjectHelper();
    ObjectHelper(QObject * opb);

public: // const
    QMetaEnum metaEnum(const KeySeg &enumName) const;
    QStringList enumNames(const bool all=false) const;
    QStringList enumKeys(const KeySeg &enumName) const;
    int flagRange(const KeySeg &enumName, const KeySeg &fromValueName, const KeySeg &toValueName) const;

public: // pointer
    QObject * object() const;
    const QMetaObject *metaObject() const;

public: // non-const

private:
    QObject * mpObject=nullptr;
};

inline QObject *ObjectHelper::object() const
{
    return mpObject;
}
