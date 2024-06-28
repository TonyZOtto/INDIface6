#pragma once
#include "IfCore.h"

#include <QObject>

#include <QMap>

#include "../eIRbase/AText.h"
#include "../eIRbase/KeyMap.h"
#include "../eIRcore/MutexQueue.h"

#include "Image.h"
#include "ImageWriterItem.h"
class ImageWriterOutput;
class ImageWriterThread;

class IFCORE_EXPORT ImageWriterManager : public QObject
{
    Q_OBJECT
public: // ctors
    explicit ImageWriterManager(QObject *parent = nullptr);
    ~ImageWriterManager();

public slots:
    void start(const KeyMap &aOutputSettings);
    void quit();
    void terminate();

public: // const
    bool isEmpty() const;
    bool notEmpty() const { return ! isEmpty(); }
    bool isQuitting() const;

public: // non-const
    void add(ImageWriterOutput * pOut);
    void set(const AText &aFormat, const int aQuality);
    ImageWriterItem takeItem();

public: // pointers
    ImageWriterThread * thread();

private: // non-const
    void startFrameDirs(const KeyMap &aOutputFrameSettings);
    void startFaceDirs(const KeyMap &aOutputFaceSettings);
    void startCropDirs(const KeyMap &aOutputCropSettings);

signals:

private:
    ImageWriterThread * mpThread=nullptr;
    bool mIsQuitting=false;
    AText mFormat=AText("PNG");
    int mQuality=90;
    QMap<Image::Type, ImageWriterOutput *> mTypeOutputMap;
    MutexQueue<ImageWriterItem> mItemQueue;
};

inline bool ImageWriterManager::isQuitting() const { return mIsQuitting; }
inline ImageWriterThread *ImageWriterManager::thread() { Q_CHECK_PTR(mpThread); return mpThread; }
