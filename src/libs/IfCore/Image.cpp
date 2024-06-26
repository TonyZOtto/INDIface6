#include "Image.h"

#include <QMetaEnum>

#include "../eIRcore/ObjectHelper.h"

Image::Image(QObject *parent) : QObject{parent} {;}

QString Image::typeName(const Type aType)
{
    ObjectHelper tOH(new Image);
    const QMetaEnum cMetaEnum = tOH.metaEnum("Type");
    return cMetaEnum.valueToKey(aType);
}
