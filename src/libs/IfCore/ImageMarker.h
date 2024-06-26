#pragma once
#include "IfCore.h"


#include "ColorImage.h"

class KeyMap;

#include "Image.h"

class IFCORE_EXPORT ImageMarker : public ColorImage
{
public: // types

public: // ctors
    ImageMarker(const Image::Type aType, const ColorImage &aInputImage);

public: // const

public: // non-const
    bool mark(const KeyMap &aMarkSettings);

private:
    bool markInputFrame(const KeyMap &aMarkSettings);
    bool markMarkedFrame(const KeyMap &aMarkSettings);
    bool markDetectFrame(const KeyMap &aMarkSettings);

private:
    const Image::Type cmType;
    const ColorImage cmInputImage;

};
