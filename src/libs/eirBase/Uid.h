#pragma once
#include "eIRbase.h"

#include <QList>
#include <QUuid>

#include "QQBitArray.h"
#include "Types.h"

/*  UUID:   00112233-4455-6677-8899-aabbccddeeff
 *  BitIndex:\-0^-16 ^-32 ^-48 ^-64 ^-80^-96^-112\=128
 *  Ver 7:  018ede8a-1e00-7d81-a387-223b32bfdb16
 *  Var 4:  018ede8a-d384-73f6-8468-b29dc030df18
 *  OurBase:00112233-4455-4677-E899-aabbccddeeff
 *                             ^--Variant (0b1110)
 *                        ^--Version
 *      Random Version 4--^    ^--Variant 7 (Reserved)
 *          ^^^^^^^^ ^^^^--Key (48 bits)
 *                         ^^^--Type (12 bits)
 *                             1^^^--Class (13 bits)
 *                                  ^^^^^^^^^^^^--Value (48 bits)
 */

class EIRBASE_EXPORT Uid
{
public: // types
    static const QUuid::Variant Variant7 = QUuid::Variant(7);
    static const Count BitCount = sizeof(OWORD) * 8U;
    typedef union
    {
        OWORD   u128;
        struct
        {
            DWORD   d0;
            WORD    w4;
            WORD    w6;
            WORD    w8;
            DWORD   dA;
            WORD    wE;
        };
        struct
        {
            QWORD   hi;
            QWORD   lo;
        };
    } Union;
    enum Type
    {
        $nullType   = 0,
        Reserved01  = 0x001,
        Reserved02  = 0x002,
        Reserved03  = 0x004,
        Reserved04  = 0x008,
        Reserved05  = 0x010,
        Reserved06  = 0x020,
        Reserved07  = 0x040,
        Reserved08  = 0x080,
        Reserved09  = 0x100,
        Reserved10  = 0x200,
        Reserved11  = 0x400,
        Reserved12  = 0x800
    };
    enum Klass
    {
        $nullKlass          = 0,
        BaseCacheEntry,
    };
    typedef QList<Uid> List;

public: // ctors
    Uid(); // null
    Uid(const bool init); // ver4 var7 random
    Uid(const Klass k, const Type t=$nullType);

public: // const
    QUuid::Variant variant() const;
    QUuid::Version version() const;
    Union toUnion() const;
    OWORD toOWord() const;
    QQBitArray toBitArray() const;
    QWORD hi() const;
    QWORD lo() const;
    Type type() const;
    Klass klass() const;
    QWORD key() const;
    QWORD value() const;
    bool operator < (const Uid &rhs) const;
    operator QUuid () const;

public: // non-const
    void set(const QWORD hi, const QWORD lo);
    void set(const OWORD ow);
    void set(const Union u);
    void set(const QQBitArray bta);
    void variant(const QUuid::Variant v);
    void version(const QUuid::Version v);
    void hi(const QWORD qw);
    void lo(const QWORD qw);
    void type(const Type t);
    void klass(const Klass k);
    void key(const QWORD qw48);
    void value(const QWORD qw48);

private: // static
    static QQBitArray variantMask();
    static QQBitArray versionMask();
    static Count variantBitCount()      { return 3; }
    static Count versionBitCount()      { return 4; }
    static Index variantBitOffset()     { return 64; }
    static Index versionBitOffset()     { return 48; }

private:
    QUuid mUuid;
};

