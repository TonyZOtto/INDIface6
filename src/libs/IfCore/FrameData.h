#pragma once
#include "IfCore.h"

#include "../eIRbase/KeyMap.h"

#include "../eIRbase/Key.h"
#include "../eIRbase/Uid.h"

class IFCORE_EXPORT FrameData : public KeyMap
{
public: // ctors
    explicit FrameData();
    FrameData(const Ident aIdent);
    FrameData(const Key aKey);

public: // const
    Uid frameUid() const;
    Key frameKey() const;
    QByteArray rawBytes() const;

public: // non-const
    void set(const Key aKey, const QVariant &aValue);

private:
};

