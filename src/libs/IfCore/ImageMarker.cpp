#include "ImageMarker.h"

#include "Image.h"

ImageMarker::ImageMarker(const Image::Type aType, const ColorImage &aInputImage)
    : cmType(aType), cmInputImage(aInputImage) {;}

bool ImageMarker::mark(const KeyMap &aMarkSettings)
{
    bool result = false;
    switch (cmType)
    {
    case Image::InputFrame:     result = markInputFrame(aMarkSettings);     break;
    case Image::MarkedFrame:    result = markMarkedFrame(aMarkSettings);    break;
    case Image::DetectFrame:    result = markDetectFrame(aMarkSettings);    break;

    default:            /* leave false result */                            break;
    }
    return result;
}

bool ImageMarker::markInputFrame(const KeyMap &aMarkSettings)
{
    Q_ASSERT(!"MUSTDO"); Q_UNUSED(aMarkSettings); return false; // MUSTDO
}

bool ImageMarker::markMarkedFrame(const KeyMap &aMarkSettings)
{
    Q_ASSERT(!"MUSTDO"); Q_UNUSED(aMarkSettings); return false; // MUSTDO
}

bool ImageMarker::markDetectFrame(const KeyMap &aMarkSettings)
{
    Q_ASSERT(!"MUSTDO"); Q_UNUSED(aMarkSettings); return false; // MUSTDO
}
