#include "FrameData.h"

FrameData::FrameData() {;}
FrameData::FrameData(const Ident aIdent) : KeyMap(aIdent) {;}
FrameData::FrameData(const Key aKey) : KeyMap(aKey) {;}

Uid FrameData::frameUid() const
{
    return ident().uid();
}

Key FrameData::frameKey() const
{
    return ident().key();
}

QByteArray FrameData::rawBytes() const
{
    return get("Input/Source/FileBytes").toByteArray();
}
