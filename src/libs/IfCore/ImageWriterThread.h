#pragma once
#include "IfCore.h"

#include <QObject>
#include <QThread>

#include <QFileInfo>

#include "../eirBase/BaseErrorCode.h"
#include "../eirBase/Key.h"
#include "../eIRbase/Types.h"

class ImageWriterManager;

class IFCORE_EXPORT ImageWriterThread : public QThread
{
    Q_OBJECT
public: // ctors
    explicit ImageWriterThread(ImageWriterManager *parent = nullptr);

public slots:

signals:
    void fileWritten(const Key &imageKey, const QFileInfo &fileInfo);
    void fileWriteError(const Key &imageKey, const BaseErrorCode &error);


public: // const

public: // non-const
    void run() override;

public: // pointers
    ImageWriterManager * manager();


private:
    ImageWriterManager * mpManager=nullptr;
    EpochMilliseconds mShortSleepMsec=100;
    EpochMilliseconds mLongSleepMsec=1000;
};

inline ImageWriterManager *ImageWriterThread::manager() { Q_CHECK_PTR(mpManager); return mpManager; }
