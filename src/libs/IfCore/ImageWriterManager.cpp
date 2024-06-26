#include "ImageWriterManager.h"

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

void ImageWriterManager::start()
{
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

ImageWriterItem ImageWriterManager::takeItem()
{
    return mItemQueue.dequeue();
}
