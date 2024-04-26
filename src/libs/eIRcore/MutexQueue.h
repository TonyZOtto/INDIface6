#pragma once

#include <QQueue>

#include <QMutex>

#include "../eIRbase/Types.h"

template <typename T>
class MutexQueue
{
public:
    MutexQueue() {;}

public: // const
    bool isEmpty() const { return mTQueue.isEmpty(); }
    bool notEmpty() const { return ! isEmpty(); }
    Count count() const { return mTQueue.count(); }

public: // non-const
    void enqueue(const T &t) { QMutex lock; mTQueue.enqueue(t); }
    T dequeue() { QMutex lock; return mTQueue.dequeue(); }

private:
    QQueue<T> mTQueue;
};