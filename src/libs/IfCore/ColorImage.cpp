#include "ColorImage.h"

ColorImage::ColorImage()
{
    format(ColorFormat);
}

ColorImage::ColorImage(const BaseImage &base)
    : BaseImage(base.convertedTo(ColorFormat))
{
}
