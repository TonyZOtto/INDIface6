#include "ColorImage.h"

ColorImage::ColorImage()
{

}

ColorImage::ColorImage(const QImage &aQImage)
    : BaseImage(aQImage, ColorFormat)
{

}

ColorImage::ColorImage(const BaseImage &aBaseImage)
    : BaseImage(aBaseImage, ColorFormat)
{

}
