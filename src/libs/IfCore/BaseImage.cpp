#include "BaseImage.h"

#include <QByteArray>
#include <QByteArrayList>
#include <QImageReader>

BaseImage::BaseImage() {;}
BaseImage::BaseImage(const QImage in, const QImage::Format format, const Count clip) { set(in, format, clip); }

bool BaseImage::isNull() const
{
    return QImage::Format_Invalid == format() || image().isNull();
}

BaseImage BaseImage::convertedTo(const QImage::Format fmt) const
{
    BaseImage result = *this;
    result.image().convertTo(fmt);
    result.format(fmt);
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

KeySegList BaseImage::smSupportedFileFormats;
QQStringList BaseImage::smSupportedFileExtensionList;

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
