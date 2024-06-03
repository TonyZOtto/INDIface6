#include "Key.h"

bool Key::isNull() const
{
    return mSegments.isEmpty();
}

bool Key::isEmpty() const
{
    return mSegments.isEmpty();
}

bool Key::isSectioned() const
{
    return ! mSegments.isEmpty();
}

bool Key::isValid(const Index ix) const
{
    return ix >= 0 && ix < (Index)(count());
}

bool Key::contains(const char ch) const
{
    return toString().contains(ch);
}

Count Key::count() const
{
    return mSegments.count();
}

KeySeg Key::segment(const Index ix) const
{
    return isValid(ix) ? mSegments.at(ix) : KeySeg();
}

KeySeg::List Key::segments(const Index ix, const Index n) const
{
    KeySeg::List result;
    const Index ixEnd = (n < 0) ? (count() - 1) : (ix + n - 1);
    if (isValid(ix) && isValid(ixEnd))
        for (Index i = ix; i <= ixEnd; ++i)
            result.append(segment(i));
    return result;
}

QString Key::sortable() const
{
    return toString().toCaseFolded();
}

QString Key::toString() const
{
    return joinString(mSegments);
}

bool Key::operator <(const Key &rhs) const
{
    return toString() < rhs.toString();
}

bool Key::operator ==(const Key &rhs) const
{
    return toString() == rhs.toString();
}

KeySeg::List Key::split(const AText &atx, const QChar hinge)
{
    KeySeg::List result;
    AText::List tAtxs = atx.split(hinge.cell());
    foreach (AText tAtx, tAtxs)
        result.append(KeySeg(tAtx));
    return result;
}

void Key::set(const char *pch)
{
    mSegments = split(AText(pch));
}

void Key::set(const AText &atx)
{
    mSegments = split(atx);
}

void Key::set(const QString &qs)
{
    mSegments = split(AText(qs));
}

void Key::set(const KeySeg::List &segs)
{
    mSegments = segs;
}

void Key::set(const char *chars, const char *chars1, const char *chars2, const char *chars3)
{
    set(QString(chars));
    append(QString(chars1));
    append(QString(chars2));
    append(QString(chars3));
}

void Key::append(const QString &s)
{
    mSegments.prepend(KeySeg(s));
}

void Key::prepend(const KeySeg &seg)
{
    mSegments.prepend(seg);
}

void Key::prepend(const Key &key)
{
    foreach (const KeySeg cSeg, key.segments()) prepend(cSeg);
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
