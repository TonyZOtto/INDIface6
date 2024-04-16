#include "Uid.h"

Uid::Uid() {;}

Uid::Uid(const bool init)
    : mUuid(QUuid::createUuid())
{
    (void)init;
    variant(Variant7);
    version(QUuid::Random);
}

Uid::Uid(const Klass k, const Type t)
    : mUuid(QUuid::createUuid())
{
    variant(Variant7),
    version(QUuid::Random),
    klass(k),
    type(t);
}

Uid::operator QUuid() const
{
    return mUuid;
}

void Uid::set(const OWORD ow)
{
    mUuid = QUuid::fromUInt128(ow);
}

void Uid::set(const QQBitArray bta)
{
    set(bta.toOWord());
}

void Uid::variant(const QUuid::Variant v)
{
    const QQBitArray cXBitMask = variantMask().toggled();
    QQBitArray tValueBits(BitCount);
    QQBitArray tUidBits(toOWord());
    tValueBits.set(variantBitOffset(), variantBitCount(), unsigned(v));
    tUidBits &= cXBitMask;
    tUidBits |= tValueBits;
    set(tUidBits);
}

void Uid::version(const QUuid::Version v)
{
    const QQBitArray cXBitMask = versionMask().toggled();
    QQBitArray tValueBits(BitCount);
    QQBitArray tUidBits(toOWord());
    tValueBits.set(versionBitOffset(), versionBitCount(), unsigned(v));
    tUidBits &= cXBitMask;
    tUidBits |= tValueBits;
    set(tUidBits);
}

QQBitArray Uid::variantMask()
{
    static QQBitArray sBitArray;
    if (sBitArray.isNull())
    {
        sBitArray.fill(false, BitCount);
        sBitArray.set(variantBitOffset(), variantBitCount());
    }
    return sBitArray;
}

QQBitArray Uid::versionMask()
{
    static QQBitArray sBitArray;
    if (sBitArray.isNull())
    {
        sBitArray.fill(false, BitCount);
        sBitArray.set(versionBitOffset(), versionBitCount());
    }
    return sBitArray;
}

OWORD Uid::toOWord() const
{
    return mUuid.toUInt128();
}

QQBitArray Uid::toBitArray() const
{
    return QQBitArray();
}
