#include "BaseImage.h"

#include <QByteArray>
#include <QByteArrayList>
#include <QImageReader>

BaseImage::BaseImage() {}

// ------------------------- static --------------------

KeySegList BaseImage::smSupportedFileFormats;
QStringList BaseImage::smSupportedFileExtensionList;

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

QStringList BaseImage::supportedFileExtensionList()
{
    QStringList result = smSupportedFileExtensionList;
    if (result.isEmpty())
    {
        const KeySegList cKSL = smSupportedFileFormats;
        foreach (const KeySeg cKS, cKSL)
        {
            result.append("*." + cKS());
        }
        smSupportedFileExtensionList = result;
    }
    return result;
}
