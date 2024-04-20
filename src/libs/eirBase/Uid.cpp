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

AText Uid::tail() const
{
    return mUuid.toByteArray().right(14);
}

void Uid::set(const OWORD ow)
{
    mUuid = QUuid::fromUInt128(ow);
}

void Uid::set(const Union u)
{
    mUuid = QUuid::fromUInt128(u.u128);
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

Uid::Union Uid::toUnion() const
{
    Uid::Union result;
    result.u128 = toOWord();
    return result;
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

Uid::Type Uid::type() const
{
    Uid::Type result = $nullType;
    const Union cUnion = toUnion();
    const WORD cW6 = cUnion.w6;
    result = Uid::Type(cW6 & 0x0FFF);
    return result;
}

void Uid::type(const Type t)
{
    Union tUnion = toUnion();
    tUnion.w6 = (tUnion.w6 & 0xF000) | (t & 0x0FFF);
    set(tUnion);
}


void Uid::klass(const Klass k)
{
    Union tUnion = toUnion();
    tUnion.w8 = (tUnion.w8 & 0xE000) | (k & 0x1FFF);
    set(tUnion);
}

Uid::Klass Uid::klass() const
{
    Uid::Klass result = $nullKlass;
    const Union cUnion = toUnion();
    const WORD cW6 = cUnion.w8;
    result = Uid::Klass(cW6 & 0x1FFF);
    return result;
}

bool Uid::operator <(const Uid &rhs) const
{
    return toOWord() < rhs.toOWord();
}

bool Uid::operator ==(const Uid &rhs) const
{
    return toOWord() == rhs.toOWord();
}
