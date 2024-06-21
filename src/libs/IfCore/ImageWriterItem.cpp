#include "ImageWriterItem.h"

#include <QBuffer>
#include <QFileInfo>

#include "../eirBase/Types.h"

class ImageWriterItemData : public QSharedData
{
public:
    Ident           Ident;
    Image::Type     Type;
    QByteArray      Format;
    int             Quality;
    QImage          Image;
    QByteArray      Bytes;
    QFileInfo       FileInfo;
};

ImageWriterItem::ImageWriterItem()
    : data(new ImageWriterItemData)
{
    data->Format = "PNG", data->Quality = 90;
}

ImageWriterItem::ImageWriterItem(const ImageWriterItem &rhs)
    : data{rhs.data}
{}

ImageWriterItem &ImageWriterItem::operator=(const ImageWriterItem &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

ImageWriterItem::~ImageWriterItem() {}

void ImageWriterItem::set(const Ident &aIdent, const Image::Type &aType)
{
    data->Ident = aIdent, data->Type = aType;
}

void ImageWriterItem::set(const char *aFormat, const int aQualty)
{
    data->Format = aFormat, data->Quality = aQualty;
}

void ImageWriterItem::set(const QImage &aImage)
{
    data->Image = aImage;
}

void ImageWriterItem::set(const QByteArray &aImageBytes)
{
    data->Bytes = aImageBytes;
}

void ImageWriterItem::set(const QDir &aDir, const QString &aBaseFileName)
{
    data->FileInfo = QFileInfo(aDir, aBaseFileName + "." + data->Format);
}

BaseErrorCode ImageWriterItem::write()
{
    BaseErrorCode result;
    if ( ! data->FileInfo.isWritable())
        result = BaseErrorCode("IfCore/ImageWriterItem/FileInfoNotWritable");
    else if (data->Bytes.isEmpty() && data->Image.isNull())
        result = BaseErrorCode("IfCore/ImageWriterItem/ImageNull");
    if ( ! result)
    {
        QBuffer tBuffer(&data->Bytes);
        tBuffer.open(QIODevice::WriteOnly);
        data->Image.save(&tBuffer, data->Format.constData(), data->Quality);
    }
    if (data->Bytes.isEmpty())
        result = BaseErrorCode("IfCore/ImageWriterItem/BytesEmpty");
    if ( ! result)
    {
        QFile tFile(data->FileInfo.absoluteFilePath());
        if ( ! tFile.open(QIODevice::WriteOnly))
            result = BaseErrorCode("IfCore/ImageWriterItem/NotOpenForWrite");
        if ( ! result)
        {
            const Count tBytesCount = data->Bytes.count();
            const Count tWriteCount = tFile.write(data->Bytes);
            if (tBytesCount != tWriteCount)
                result = BaseErrorCode("IfCore/ImageWriterItem/WriteFailure",
                    QString("Writing %1 to %2, Expected %3 bytes, Wrote %4 bytes")
                                           .arg(data->Ident.key()(),
                                                data->FileInfo.absoluteFilePath())
                                           .arg(tBytesCount).arg(tWriteCount));
        }
    }
    return result;
}

