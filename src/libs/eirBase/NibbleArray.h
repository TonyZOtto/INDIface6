#pragma once

#include <QByteArray>

#include "Nibble.h"
#include "Types.h"

class NibbleArray : private QByteArray
{
public:
    NibbleArray();
//    NibbleArray(const Count k, const Nibble fill=0);
};
