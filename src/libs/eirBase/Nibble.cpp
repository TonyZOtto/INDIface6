#include "Nibble.h"

Nibble Nibble::nibble()
{
    return mUnsigned & 0x000000000000000F;
}
