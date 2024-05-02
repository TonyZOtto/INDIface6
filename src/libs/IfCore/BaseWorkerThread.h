#pragma once

#include <QThread>

#include "BaseWorkerTask.h"

class BaseWorkerThread : public QThread
{
    Q_OBJECT
public: // ctors
    explicit BaseWorkerThread(QObject *parent = nullptr);

public: // ctors

public: // non-const

public: // virtual non-const
    virtual void run() = 0; // pure

protected:
};
