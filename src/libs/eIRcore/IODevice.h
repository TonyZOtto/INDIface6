#pragma once
#include "eIRcore.h"

#include <QIODevice>

class EIRCORE_EXPORT IODevice
{
public:
    IODevice();

public: // static
    static QIODevice::OpenMode openMode(const QStringList &modes);
};
