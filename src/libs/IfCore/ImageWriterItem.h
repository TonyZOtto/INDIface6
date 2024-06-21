#pragma once

#include <QSharedDataPointer>

#include <QByteArray>
#include <QDir>
#include <QImage>
#include <QString>

#include "../eirBase/BaseErrorCode.h"
#include "../eirBase/Ident.h"
#include "../IfCore/Image.h"

class ImageWriterItemData;

class ImageWriterItem
{
public:
    ImageWriterItem();
    ImageWriterItem(const ImageWriterItem &);
    ImageWriterItem &operator=(const ImageWriterItem &);
    ~ImageWriterItem();

public:
    void set(const Ident &aIdent, const Image::Type &aType);
    void set(const char *aFormat, const int aQualty);
    void set(const QImage &aImage);
    void set(const QByteArray &aImageBytes);
    void set(const QDir &aDir, const QString &aBaseFileName);
    BaseErrorCode write();

private:
    QSharedDataPointer<ImageWriterItemData> data;
};
