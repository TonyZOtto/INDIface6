#pragma once
#include "IfCore.h"

#include <QObject>

class IFCORE_EXPORT ImageWriterManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageWriterManager(QObject *parent = nullptr);

signals:
};
