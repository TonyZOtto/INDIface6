#include "IODevice.h"

IODevice::IODevice() {}

QIODeviceBase::OpenMode IODevice::openMode(const QStringList &modes)
{
    QIODeviceBase::OpenMode result = QIODevice::NotOpen;
    if (modes.contains("ReadOnly"))         result |= QIODevice::ReadOnly;
    if (modes.contains("WriteOnly"))        result |= QIODevice::WriteOnly;
    if (modes.contains("ReadWrite"))        result |= QIODevice::ReadWrite;
    if (modes.contains("Append"))           result |= QIODevice::Append;
    if (modes.contains("Truncate"))         result |= QIODevice::Truncate;
    if (modes.contains("Text"))             result |= QIODevice::Text;
    if (modes.contains("Unbuffered"))       result |= QIODevice::Unbuffered;
    if (modes.contains("NewOnly"))          result |= QIODevice::NewOnly;
    if (modes.contains("ExistingOnly"))     result |= QIODevice::ExistingOnly;
    return result;
}
