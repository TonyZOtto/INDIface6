#pragma once

#include <QObject>

#include "../eIRbase/Ident.h"

class FrameData
{
    Q_GADGET
public:
    explicit FrameData();

    // -------------------- Properties ------------------
    Ident p_ident;
};
