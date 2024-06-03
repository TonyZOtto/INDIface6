#pragma once
#include "IfCore.h"

#include "../eIRbase/KeyMap.h"

#include "../eIRbase/Ident.h"
#include "../eIRbase/Key.h"
#include "../eIRbase/Uid.h"

class IFCORE_EXPORT FrameData : public KeyMap
{
public: // ctors
    explicit FrameData();
    FrameData(const Ident i);

public: // const
    Ident ident() const;
    Uid frameUid() const;
    Key frameKey() const;

public: // non-const

private:
    Ident mIdent;
};

inline Ident FrameData::ident() const { return mIdent; }
