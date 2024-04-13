#pragma once

#include <QThread>

#include <MutexQueue.h>

class BaseConsoleWorker;

class BaseConsoleThread : public QThread
{
    Q_OBJECT
public:
    explicit BaseConsoleThread(QObject *parent = nullptr);

private:
    MutexQueue<BaseConsoleWorker *> mInputWorkerQueue;
    MutexQueue<BaseConsoleWorker *> mOutputWorkerQueue;
};
