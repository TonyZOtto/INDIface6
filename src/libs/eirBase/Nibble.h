#pragma once

#include "Types.h"

class Nibble
{
public:
    Nibble()                : mUnsigned(0)          {;}
    Nibble(const BYTE b)    : mUnsigned(b  & 0xF)   {;}
    Nibble(const WORD w)    : mUnsigned(w  & 0xF)   {;}
    Nibble(const DWORD dw)  : mUnsigned(dw & 0xF)   {;}
    Nibble(const QWORD qw)  : mUnsigned(qw & 0xF)   {;}

public:
    Nibble nibble();


private:
    unsigned mUnsigned;
};
