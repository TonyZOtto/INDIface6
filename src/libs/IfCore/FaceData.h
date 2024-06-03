#pragma once
#include "IfCore.h"

#include "../eIRbase/KeyMap.h"

#include "../eIRbase/Ident.h"
#include "../eIRbase/Key.h"
#include "../eIRbase/Types.h"
#include "../eIRbase/Uid.h"

class IFCORE_EXPORT FaceData : public KeyMap
{
public: // ctors
    explicit FaceData();
    FaceData(const Ident face, const Ident frame, const Index faceIx);

public: // const
    Ident faceIdent();
    Uid faceUid() const;
    Key faceKey() const;
    Index faceIndex() const;
    Ident frameIdent();
    Uid frameUid() const;
    Key frameKey() const;

public: // non-const

private:
    Ident mFaceIdent;
    Ident mFrameIdent;
    Index mFrameFaceIndex = 0; // origin 1
};
