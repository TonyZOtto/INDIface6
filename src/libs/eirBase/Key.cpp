#include "Key.h"

bool Key::isNull() const
{
    return mSegments.isEmpty();
}

QString Key::toString() const
{
    return joinString(mSegments);
}

bool Key::operator <(const Key &rhs) const
{
    return toString() < rhs.toString();
}

KeySeg::List Key::split(const AText &atx, const QChar hinge)
{
    KeySeg::List result;
    AText::List tAtxs = atx.split(hinge.cell());
    foreach (AText tAtx, tAtxs)
        result.append(KeySeg(tAtx));
    return result;
}


// =================== static ====================

QString Key::joinString(const KeySeg::List &segs, const QChar hinge)
{
    QString result;
    foreach (const KeySeg cSeg, segs)
        result += cSeg.toString() + hinge;
    result.chop(1);
    return result;
}
