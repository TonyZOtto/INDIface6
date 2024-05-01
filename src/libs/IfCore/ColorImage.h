#pragma once
#include "IfCore.h"

#include "BaseImage.h"

class IFCORE_EXPORT ColorImage : public BaseImage
{
public:
    ColorImage();
    ColorImage(const BaseImage &base);

};
