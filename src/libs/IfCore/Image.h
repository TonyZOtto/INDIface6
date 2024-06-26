#pragma once
#include "IfCore.h"

#include <QObject>

class IFCORE_EXPORT Image : public QObject
{
    Q_OBJECT
public: // types
    enum Type
    {
        $null = 0,
        $beginFrame,
        CaptureFrame,
        InputFrame,
        MarkedFrame,
        DetectFrame,
        $endFrame,
        $beginFace,
        EyeDetectFace,
        $endFace,
        $beginCrop,
        BodyMarked,
        $endCrop,
        $endType
    };
    Q_ENUM(Type)
    static QString typeName(const Type aType);

public: // ctors
    explicit Image(QObject *parent = nullptr);

public: // const
    bool isFrameType() const;
    bool isFaceType() const;
    bool isCropType() const;
    QMetaEnum typeMetaEnum() const;

signals:
};
