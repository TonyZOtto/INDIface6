#pragma once
#include "IfCore.h"

#include "../eIRcore/BaseUidCache.h"
#include "BaseImage.h"
#include "FaceData.h"
#include "FrameData.h"

class IFCORE_EXPORT IfCache : public BaseUidCache
{
    Q_OBJECT
public: // ctors
    explicit IfCache(QObject *parent = nullptr);

public: // const
    BaseImage image(const Key &key);
    FrameData frame(const Key &key);
    FaceData face(const Key &key);
    FaceData face(const Key &frameKey, const Index &faceIndex);

public: // non-const
    void image(const Key &key, const BaseImage &image);
};
