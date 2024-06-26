#pragma once
#include "IfCore.h"

#include "../eIRbase/KeyMap.h"

#include <QByteArray>
#include <QFileInfo>
#include <QImage>
#include <QUrl>

#include "../eIRbase/Key.h"
#include "../eIRbase/Uid.h"

#include "ColorImage.h"
#include "Image.h"

class IFCORE_EXPORT FrameData : public KeyMap
{
public: // ctors
    explicit FrameData();
    FrameData(const Ident aIdent);
    FrameData(const Key aKey);

public: // const
    Uid frameUid() const;
    Key frameKey() const;
    QByteArray rawBytes() const;
    KeyMap settings(const Image::Type aIType);

public: // non-const
    void settings(const KeyMap &aMarkFrameMap);
    void sourceUrl(const QUrl &aUrl);
    void sourceFileInfo(const QFileInfo &aFileInfo);
    void sourceFileBytes(const QByteArray &aBytes);
    void sourceFileImage(const QImage &aImage);
    void sourceColorImage(const ColorImage &aColorImage);
    QImage qImage(const Image::Type &aIType);
    ColorImage colorImage(const Image::Type &aIType);

private:
    QImage generate(const Image::Type aIType);
    QImage generateInput(const Image::Type aIType);
    QImage generateMarked(const Image::Type aIType);


private:
    QMap<Image::Type, QImage> mTypeQImageMap;
    QMap<Image::Type, ColorImage> mTypeColorImageMap;
};

