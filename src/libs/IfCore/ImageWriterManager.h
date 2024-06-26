#pragma once
#include "IfCore.h"

#include <QObject>

#include "../eIRcore/MutexQueue.h"

#include "ImageWriterItem.h"
class ImageWriterThread;

class IFCORE_EXPORT ImageWriterManager : public QObject
{
    Q_OBJECT
public: // ctors
    explicit ImageWriterManager(QObject *parent = nullptr);
    ~ImageWriterManager();

public slots:
    void start();
    void quit();
    void terminate();

public: // const
    bool isEmpty() const;
    bool notEmpty() const { return ! isEmpty(); }
    bool isQuitting() const;

public: // non-const
    ImageWriterItem takeItem();

public: // pointers
    ImageWriterThread * thread();

signals:

private:
    ImageWriterThread * mpThread=nullptr;
    bool mIsQuitting=false;
    MutexQueue<ImageWriterItem> mItemQueue;
};

inline bool ImageWriterManager::isQuitting() const { return mIsQuitting; }
inline ImageWriterThread *ImageWriterManager::thread() { Q_CHECK_PTR(mpThread); return mpThread; }
