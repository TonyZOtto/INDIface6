#pragma once
#include "IfCore.h"

#include <QImage>
#include <QList>
#include <QRgb>

#include "../eIRbase/KeySeg.h"
#include "../eIRbase/KeySegList.h"
#include "../eIRcore/SizeT.h"

class IFCORE_EXPORT BaseImage
{
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

public: // static
    static QImage::Format format(const Type t);
    static Type type(const QImage::Format f);
    static KeySegList supportedFileFormats();
    static QStringList supportedFileExtensionList();

private:
    Type            mType;
    QImage::Format  mFormat;
    ColorTable      mColorTable;
    Size            mSize;
    QImage          mImage;
    QImage          mAlphaImage;
    static KeySegList smSupportedFileFormats;
    static QStringList smSupportedFileExtensionList;
};
