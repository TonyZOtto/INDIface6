#include "ImageWriterManager.h"

#include <QString>

#include "eirBase/AText.h"
#include "eirBase/KeyMap.h"
#include "ImageWriterOutput.h"
#include "ImageWriterThread.h"

ImageWriterManager::ImageWriterManager(QObject *parent)
    : QObject{parent}
    , mpThread(new ImageWriterThread(this))
{
    setObjectName("ImageWriterManager");
}

ImageWriterManager::~ImageWriterManager()
{
    if (mpThread)
    {
        mpThread->terminate();
        mpThread->wait(2000);
    }
}

void ImageWriterManager::start(const KeyMap &aOutputSettings)
{
    const QString cBaseDir = aOutputSettings.get("BaseDir").toString();
    const AText cFormat = aOutputSettings.get("Format", "PNG").toByteArray();
    const int cQuality = aOutputSettings.get("Quality", 90).toInt();
    ImageWriterOutput::setBase(cBaseDir);
    set(cFormat, cQuality);

    startFrameDirs(aOutputSettings.extract("Frame"));
    startFaceDirs(aOutputSettings.extract("Face"));
    startCropDirs(aOutputSettings.extract("Crop"));
    thread()->start(QThread::LowPriority);
}

void ImageWriterManager::quit()
{
    mIsQuitting = true;
    thread()->quit();
}

void ImageWriterManager::terminate()
{
    mIsQuitting = true;
    thread()->terminate();
}

bool ImageWriterManager::isEmpty() const
{
    return mItemQueue.isEmpty();
}

void ImageWriterManager::add(ImageWriterOutput *pOut)
{
    const Image::Type cType = pOut->type();
    if (mTypeOutputMap.contains(cType))
    {
        ImageWriterOutput * pOld = mTypeOutputMap.value(cType);
        pOld->deleteLater();
        mTypeOutputMap.remove(cType);
    }
    mTypeOutputMap.insert(cType, pOut);
}

void ImageWriterManager::set(const AText &aFormat, const int aQuality)
{
    mFormat = aFormat, mQuality = aQuality;
}

ImageWriterItem ImageWriterManager::takeItem()
{
    return mItemQueue.dequeue();
}

void ImageWriterManager::startFrameDirs(const KeyMap &aOutputFrameSettings)
{
    for (int ix = Image::$beginFrame+1; ix < Image::$endFrame; ++ix)
    {
        const Image::Type cType = Image::Type(ix);
        const QString cName = Image::typeName(cType);
        if (aOutputFrameSettings.contains(cName))
        {
            ImageWriterOutput * pOut = new ImageWriterOutput(cType, this);
            add(pOut);
        }
    }
}

void ImageWriterManager::startFaceDirs(const KeyMap &aOutputFaceSettings)
{
    Q_UNUSED(aOutputFaceSettings);   // NEEDDO ImageWriterManager::startFaceDirs();

}

void ImageWriterManager::startCropDirs(const KeyMap &aOutputCropSettings)
{
    Q_UNUSED(aOutputCropSettings); // NEEDDO ImageWriterManager::startCropDirs();
}
