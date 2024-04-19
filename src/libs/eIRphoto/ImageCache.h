#pragma once
#include "eIRphoto.h"

#include "../eIRcore/BaseUidCache.h"
#include "BaseImage.h"

class EIRPHOTO_EXPORT ImageCache : public BaseUidCache
{
    Q_OBJECT
public: // ctors
    explicit ImageCache(QObject *parent = nullptr);

public: // const
    BaseImage image(const Key &valueKey);

public: // non-const
    void image(const Key &valueKey, const BaseImage &image);
};
