#include "ImageWriterThread.h"

#include "ImageWriterItem.h"
#include "ImageWriterManager.h"

ImageWriterThread::ImageWriterThread(ImageWriterManager *parent)
    : QThread{parent}
    , mpManager(parent)
{
    setObjectName("ImageWriterThread");
}

void ImageWriterThread::run()
{
    while ( ! manager()->isQuitting())
    {
        if (manager()->notEmpty())
        {
            ImageWriterItem tItem = manager()->takeItem();
            if (tItem.notNull())
            {
                const BaseErrorCode cBEC = tItem.write();
            }
            msleep(mShortSleepMsec);
        }
        else
        {
            msleep(mLongSleepMsec);
        }
    }
}
