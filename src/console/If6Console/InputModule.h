#pragma once

#include "VirtualIfModule.h"

#include <QFileInfo>
#include <QUrl>

#include <Types.h>
#include <Uid.h>
#include <MutexQueue.h>
#include <QQFileInfo.h>
#include <QQString.h>
#include <QQStringList.h>
class BaseErrorCode;

class InputSettings;

class InputModule : public VirtualIfModule
{
    Q_OBJECT
public:
    explicit InputModule(IfConsoleApp *parent = nullptr);

public slots:
    virtual void initialize();
    virtual void run();

signals:
    void initialized(VirtualIfModule * pThis);
    void running();
    void allFiles(const QFileInfoList &fileList);
    void empty();
    void startProcessing(const Count nFiles);
    void finishedProcessing(const Count nProcessed);
    void processing(const QFileInfo &fi);
    void processed(const Count nProcessed, const QFileInfo &fi);
    void processError(const Count nNull, const QFileInfo &fi, const BaseErrorCode &ec);
    void cachedFrame(const Uid aUid);

public: // const
    QFileInfoList fileInfoList() const;

public: // non-const
    void start(const QUrl &url);

public: // pointers

private:
    void startFiles(const QUrl &url, const QUrlQuery &query);
    void startHotDir(const QUrl &url, const QUrlQuery &query);
    void startHttp(const QUrl &url, const QUrlQuery &query);
    bool processFiles(const QFileInfoList &aFIList);
    BaseErrorCode processFile(const QFileInfo fi);

    static QQStringList enumerateExtensions(const QUrlQuery &query);
    static QDir dir(const QUrl &url);

private:
    QFileInfoList mFileInfoList;
    MutexQueue<Uid> mCacheUidQueue;
};

inline QFileInfoList InputModule::fileInfoList() const { return mFileInfoList; }
