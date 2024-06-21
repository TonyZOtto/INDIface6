#pragma once
#include "IfCore.h"

#include <QObject>
#include <QThread>

class IFCORE_EXPORT ImageWriterThread : public QThread
{
    Q_OBJECT
public:
    explicit ImageWriterThread(QObject *parent = nullptr);

signals:
};
