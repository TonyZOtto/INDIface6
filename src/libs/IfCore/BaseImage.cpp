#include "BaseImage.h"

#include <QByteArray>
#include <QByteArrayList>
#include <QDataStream>
#include <QImageReader>

const QImage::Format BaseImage::MonoFormat = QImage::Format_Mono;
const QImage::Format BaseImage::TableFormat = QImage::Format_Indexed8;
const QImage::Format BaseImage::Table16Format = QImage::Format_Grayscale16;
const QImage::Format BaseImage::GreyScaleFormat = QImage::Format_Grayscale8;
const QImage::Format BaseImage::GreyScale16Format = QImage::Format_Grayscale16;
const QImage::Format BaseImage::ColorFormat = QImage::Format_ARGB32;
const QImage::Format BaseImage::FloatColorFormat = QImage::Format_RGBA16FPx4;
const QImage::Format BaseImage::AlphaFormat = QImage::Format_Alpha8;
const QImage::Format BaseImage::PlaneFormat = QImage::Format_Indexed8;
const QImage::Format BaseImage::FloatPlaneFormat = QImage::Format_Indexed8;


BaseImage::BaseImage() : p_type($nullType), p_format(QImage::Format_Invalid) {;}
BaseImage::BaseImage(const QImage in, const QImage::Format format, const Count clip) { set(in, format, clip); }

bool BaseImage::isNull() const
{
    return $nullType == type() || QImage::Format_Invalid == format() || image().isNull();
}

BaseImage BaseImage::convertedTo(const QImage::Format fmt) const
{
    BaseImage result = *this;
    result.image().convertTo(fmt);
    result.format(fmt);
    return result;
}

QVariant BaseImage::toVariant() const
{
    QVariant result;
    if (notNull())
    {
        QByteArray tBytes;
        QDataStream tData(&tBytes, QDataStream::WriteOnly);
        int tRectWidth = rect().size().width(), tRectHeight = rect().size().height();
        int tRectCenterX = rect().center().intX(), tRectCenterY = rect().center().intY();
        // TODO QDataStream << RectT<int>
        tData << smDatastreamKey();
        tData << p_type;
        tData << p_format;
        tData << p_colorTable;
        tData << tRectWidth;
        tData << tRectHeight;
        tData << tRectCenterX;
        tData << tRectCenterY;
        tData << p_image;
        tData << p_alphaImage;
        result.setValue(tBytes);
    }
    return result;
}

bool BaseImage::set(const QImage in, const QImage::Format format, const unsigned clip)
{
    const Rect cRectIn(in.rect());
    Q_UNUSED(clip); // TODO Handle clip
//    const Rect cRect = cRectIn.clipped(clip);
//    const QRect cQRect(cRect.topLeft().toQPoint(), cRect.size().toQSize());
//    const QImage tImage = in.convertedTo(format).copy(cQRect);
    const QImage tImage = in.convertedTo(format);
    bool result = ! tImage.isNull();
    if (result) image(tImage);
    return result;
}

// ------------------------- static --------------------

const Key BaseImage::smDatastreamKey("EIR/IfCore/BaseImage");
KeySegList BaseImage::smSupportedFileFormats;
QQStringList BaseImage::smSupportedFileExtensionList;

BaseImage BaseImage::fromVariant(const QVariant &var)
{
    BaseImage result;
    if ( ! var.isNull())
    {
        QByteArray tBytes;
        QDataStream tData(&tBytes, QDataStream::ReadOnly);
        QString tStringKey;
        tData >> tStringKey;
        const Key cStreamKey(tStringKey);
        if (cStreamKey == smDatastreamKey)
        {
            int tRectWidth, tRectHeight, tRectCenterX, tRectCenterY;
            tData >> result.p_type;
            tData >> result.p_format;
            tData >> result.p_colorTable;
            tData >> tRectWidth;
            tData >> tRectHeight;
            tData >> tRectCenterX;
            tData >> tRectCenterY;
            tData >> result.p_image;
            tData >> result.p_alphaImage;
            result.p_rect = Rect(QSize(tRectWidth, tRectHeight),
                                 QPoint(tRectCenterX, tRectCenterY));
        }
    }
    return result;
}

KeySegList BaseImage::supportedFileFormats()
{
    KeySegList result = smSupportedFileFormats;
    if (result.isEmpty())
    {
        const QByteArrayList cBAL = QImageReader::supportedImageFormats();
        foreach (const QByteArray cBA, cBAL)
        {
            KeySeg cKS(cBA);
            result.append(cKS.toUpper());
        }
        smSupportedFileFormats = result;
    }
    return result;
}

QQStringList BaseImage::supportedFileExtensionList()
{
    QQStringList result = smSupportedFileExtensionList;
    if (result.isEmpty())
    {
        const KeySegList cKSL = smSupportedFileFormats;
        foreach (const KeySeg cKS, cKSL)
        {
            result.append(QQString("*." + cKS()));
        }
        smSupportedFileExtensionList = result;
    }
    return result;
}

QQStringList BaseImage::nameFilters(const QQStringList &extList)
{
    QQStringList result;
    foreach(QQString s, extList)
        result.append("*." + s);
    return result;
}
