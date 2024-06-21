#include "ImageWriterManager.h"

ImageWriterManager::ImageWriterManager(QObject *parent)
    : QObject{parent}
{
    setObjectName("ImageWriterManager");
}
