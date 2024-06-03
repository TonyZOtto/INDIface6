#include "FrameData.h"

FrameData::FrameData() {;}
FrameData::FrameData(const Ident i) : mIdent(i) {;}

Uid FrameData::frameUid() const
{
    return ident().uid();
}

Key FrameData::frameKey() const
{
    return ident().key();
}
