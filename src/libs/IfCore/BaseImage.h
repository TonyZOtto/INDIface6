#pragma once
#include "IfCore.h"

#include <QObject>

#include <QImage>
#include <QList>
#include <QRgb>

#include "../eIRbase/KeySeg.h"
#include "../eIRbase/KeySegList.h"
#include "../eIRcore/QQStringList.h"
#include "../eIRcore/SizeT.h"

class IFCORE_EXPORT BaseImage
{
    Q_GADGET
public: // types
    enum Type
    {
        $nullType = 0,
        Mono,
        Table,
        Table16,
        GreyScale,
        GreyScale16,
        Color,
        FloatColor,
        Alpha,
        Plane,
        FloatPlane,
    };
    typedef QList<QRgb> ColorTable;
    const QImage::Format MonoFormat = QImage::Format_Mono;
    const QImage::Format TableFormat = QImage::Format_Indexed8;
    const QImage::Format Table16Format = QImage::Format_Grayscale16;
    const QImage::Format GreyScaleFormat = QImage::Format_Grayscale8;
    const QImage::Format GreyScale16Format = QImage::Format_Grayscale16;
    const QImage::Format ColorFormat = QImage::Format_ARGB32;
    const QImage::Format FloatColorFormat = QImage::Format_RGBA16FPx4;
    const QImage::Format AlphaFormat = QImage::Format_Alpha8;
    const QImage::Format PlaneFormat = QImage::Format_Indexed8;
    const QImage::Format FloatPlaneFormat = QImage::Format_Indexed8;

public: // ctors
    BaseImage();
    BaseImage(const QImage::Format format, const Size size=Size());
    BaseImage(const Type type, const Size size=Size());

public: // const
    BaseImage convertedTo(const QImage::Format fmt) const;

public: // non-const
    void convertTo(const QImage::Format fmt);

public: // static
    static QImage::Format format(const Type t);
    static Type type(const QImage::Format f);
    static KeySegList supportedFileFormats();
    static QQStringList supportedFileExtensionList();
    static QQStringList nameFilters(const QQStringList &extList);


    // --------------------- properties -------------------
    void type(Type new_type);
    QImage::Format format() const;
    void format(const QImage::Format &new_format);
    ColorTable colorTable() const;
    void colorTable(const ColorTable &new_colorTable);
    Size size() const;
    void size(const Size &new_size);
    QImage image() const;
    void image(const QImage &new_image);
    QImage alphaImage() const;
    void alphaImage(const QImage &new_alphaImage);
protected:
    Type            p_type;
    QImage::Format  p_format;
    ColorTable      p_colorTable;
    Size            p_size;
    QImage          p_image;
    QImage          p_alphaImage;
    static KeySegList smSupportedFileFormats;
    static QQStringList smSupportedFileExtensionList;
};

inline void BaseImage::type(BaseImage::Type new_type)
{
    p_type = new_type;
}

inline QImage::Format BaseImage::format() const
{
    return p_format;
}

inline void BaseImage::format(const QImage::Format &new_format)
{
    p_format = new_format;
}

inline BaseImage::ColorTable BaseImage::colorTable() const
{
    return p_colorTable;
}

inline void BaseImage::colorTable(const BaseImage::ColorTable &new_colorTable)
{
    p_colorTable = new_colorTable;
}

inline Size BaseImage::size() const
{
    return p_size;
}

inline void BaseImage::size(const Size &new_size)
{
    p_size = new_size;
}

inline QImage BaseImage::image() const
{
    return p_image;
}

inline void BaseImage::image(const QImage &new_image)
{
    p_image = new_image;
}

inline QImage BaseImage::alphaImage() const
{
    return p_alphaImage;
}

inline void BaseImage::alphaImage(const QImage &new_alphaImage)
{
    p_alphaImage = new_alphaImage;
}
