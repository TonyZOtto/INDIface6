#pragma once
#include "IfCore.h"

#include <QObject>

#include <QVariant>
#include <QImage>
#include <QList>
#include <QRgb>

#include "../eIRbase/Key.h"
#include "../eIRbase/KeySeg.h"
#include "../eIRbase/KeySegList.h"
#include "../eIRbase/Types.h"
#include "../eIRcore/QQString.h"
#include "../eIRcore/QQStringList.h"
#include "../eIRcore/RectT.h"
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
    static const QImage::Format MonoFormat;
    static const QImage::Format TableFormat;
    static const QImage::Format Table16Format;
    static const QImage::Format GreyScaleFormat;
    static const QImage::Format GreyScale16Format;
    static const QImage::Format ColorFormat;
    static const QImage::Format FloatColorFormat;
    static const QImage::Format AlphaFormat;
    static const QImage::Format PlaneFormat;
    static const QImage::Format FloatPlaneFormat;

public: // ctors
    BaseImage();
    BaseImage(const QImage::Format format, const Size size=Size());
    BaseImage(const BaseImage other, const QImage::Format format, const Count clip=0);
    BaseImage(const QImage in, const QImage::Format format, const Count clip=0);
    BaseImage(const Type type, const Size size=Size());

public: // const
    bool isNull() const;
    bool notNull() const { return ! isNull(); }
    BaseImage convertedTo(const QImage::Format fmt) const;
    QVariant toVariant() const;

public: // non-const
    void clear();
    bool set(const QImage aImage, const QImage::Format aFormat, const unsigned aClip=0);
    void convertTo(const QImage::Format fmt);

public: // static
    static BaseImage fromVariant(const QVariant &var);
    static QImage::Format format(const Type t);
    static Type type(const QImage::Format f);
    static KeySegList supportedFileFormats();
    static QQStringList supportedFileExtensionList();
    static QQStringList nameFilters(const QQStringList &extList);

    // --------------------- properties -------------------
public:
    Type type() const { return p_type; }
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
    Rect rect() const;
    void rect(const Rect &new_rect);

protected:
    Type            p_type;
    QImage::Format  p_format=QImage::Format_Invalid;
    ColorTable      p_colorTable;
    Rect            p_rect;
    QImage          p_image;
    QImage          p_alphaImage;
    static const Key smDatastreamKey;
    static KeySegList smSupportedFileFormats;
    static QQStringList smSupportedFileExtensionList;
};


// --------------------- properties -------------------

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
    return p_rect.size();
}

inline void BaseImage::size(const Size &new_size)
{
    p_rect.size(new_size);
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

inline Rect BaseImage::rect() const
{
    return p_rect;
}

inline void BaseImage::rect(const Rect &new_p_rect)
{
    p_rect = new_p_rect;
}
