#include "ImageWriterThread.h"

ImageWriterThread::ImageWriterThread(QObject *parent)
    : QThread{parent}
{
    setObjectName("ImageWriterThread");
}
