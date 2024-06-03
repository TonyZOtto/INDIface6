#pragma once
#include "IfCore.h"

#include <QMetaType>

#include "BaseImage.h"

class IFCORE_EXPORT ColorImage : public BaseImage
{
public:
    ColorImage(const QImage &qi);
#if 0
public: // QMetaType
    ColorImage() = default;
    ~ColorImage() = default;
    ColorImage(const ColorImage &) = default;
    ColorImage &operator=(const ColorImage &) = default;
#endif
};

//Q_DECLARE_METATYPE(ColorImage);
