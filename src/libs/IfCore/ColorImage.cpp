#include "ColorImage.h"

ColorImage::ColorImage()
{
    format(ColorFormat);
}

ColorImage::ColorImage(const QImage &qi)
    : BaseImage(qi, ColorFormat)
{

}
