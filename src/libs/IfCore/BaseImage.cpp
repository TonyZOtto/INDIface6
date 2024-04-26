#include "BaseImage.h"

#include <QByteArray>
#include <QByteArrayList>
#include <QImageReader>

BaseImage::BaseImage() {}

// ------------------------- static --------------------

KeySegList BaseImage::supportedFileFormats()
{
    KeySegList result;
    const QByteArrayList cBAL = QImageReader::supportedImageFormats();
    foreach (const QByteArray cBA, cBAL)
    {
        KeySeg cKS(cBA);
        result.append(cKS.toUpper());
    }
    return result;
}
