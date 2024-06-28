#include "FrameData.h"

FrameData::FrameData() {;}
FrameData::FrameData(const Ident aIdent) : KeyMap(aIdent) {;}
FrameData::FrameData(const Key aKey) : KeyMap(aKey) {;}

#include "ImageMarker.h"

Uid FrameData::frameUid() const
{
    return ident().uid();
}

Key FrameData::frameKey() const
{
    return ident().key();
}

QByteArray FrameData::rawBytes() const
{
    return get("Input/Source/FileBytes").toByteArray();
}

KeyMap FrameData::settings(const Image::Type aIType)
{
    const QVariant cValue = get("Settings/Mark/" + Image::typeName(aIType));
    return cValue.value<KeyMap>();
}

void FrameData::settings(const KeyMap &aMarkFrameMap)
{
    QVariant tValue;
    tValue.setValue(aMarkFrameMap);
    set("Settings/Mark", tValue);
}

void FrameData::sourceUrl(const QUrl &aUrl)
{
    set("Input/Source/URL", aUrl);
}

void FrameData::sourceFileInfo(const QFileInfo &aFileInfo)
{
    set("Input/Source/TimeStampMsec", aFileInfo.lastModified().toMSecsSinceEpoch());
    set("Input/Source/FileName", aFileInfo.fileName());
}

void FrameData::sourceFileBytes(const QByteArray &aBytes)
{
    set("Input/Source/FileBytes", aBytes);
}

void FrameData::sourceFileImage(const QImage &aImage)
{
    set("Input/Source/FileImage", aImage);
}

void FrameData::sourceColorImage(const ColorImage &aColorImage)
{
    set("Input/Source/ColorImage", aColorImage.toVariant());
}

QImage FrameData::qImage(const Image::Type &aIType)
{
    QImage result;
    if ( ! mTypeQImageMap.contains(aIType))
        mTypeQImageMap.insert(aIType, generate(aIType));
    result = mTypeQImageMap.value(aIType);
    return result;
}

ColorImage FrameData::colorImage(const Image::Type &aIType)
{
    ColorImage result;
    if ( ! mTypeColorImageMap.contains(aIType))
    {
        const QImage cQImage = qImage(aIType);
        mTypeColorImageMap.insert(aIType, ColorImage(cQImage));
    }
    result = mTypeColorImageMap.value(aIType);
    return result;
}

QImage FrameData::generate(const Image::Type aIType)
{
    QImage result;
    switch (aIType)
    {
    case Image::$null: /* don't generate $null type  */                break;
    case Image::InputFrame:
        result = generateInput(aIType);                         break;
    case Image::MarkedFrame:
        result = generateMarked(aIType);                        break;
    case Image::DetectFrame:
        qDebug() << Q_FUNC_INFO << "Not Supported" << aIType;   break;
    case Image::EyeDetectFace:
        qDebug() << Q_FUNC_INFO << "Not Supported" << aIType;   break;
    case Image::BodyMarked:
        qDebug() << Q_FUNC_INFO << "Not Supported" << aIType;   break;
    case Image::$beginFrame:   case Image::$endFrame:
    case Image::$beginFace:    case Image::$endFace:
    case Image::$beginCrop:    case Image::$endCrop:      case Image::$endType:
        /* ignore $marker enums */                              break;
    default:
        qDebug() << Q_FUNC_INFO << "Not Handled" << aIType;     break;
    }
    return result;
}

QImage FrameData::generateInput(const Image::Type aIType)
{
    Q_UNUSED(aIType);
    QImage result;
    const QByteArray cBytes = rawBytes();
    if (rawBytes().isEmpty())
        qWarning() << Q_FUNC_INFO << "No Raw Bytes";
    else
        result = QImage::fromData(cBytes, "PNG");
    return result;
}

QImage FrameData::generateMarked(const Image::Type aIType)
{
    Q_UNUSED(aIType);
    ImageMarker tMarker(aIType, colorImage(aIType));
    tMarker.mark(settings(aIType));
    return tMarker.image();
}

