#include "BaseImage.h"

#include <QByteArray>
#include <QByteArrayList>
#include <QImageReader>

#include <QQString.h>

BaseImage::BaseImage() {}

BaseImage BaseImage::convertedTo(const QImage::Format fmt) const
{
    BaseImage result = *this;
    result.image().convertTo(fmt);
    result.format(fmt);
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
