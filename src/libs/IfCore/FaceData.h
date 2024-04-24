#pragma once

#include <QObject>

#include "../eIRbase/Ident.h"

class FaceData
{
    Q_GADGET
public:
    explicit FaceData();

    // -------------------- Properties ------------------
    Ident p_ident;
    Ident p_FrameIdent;
    Index p_FrameFaceIndex;
};
