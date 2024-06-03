#pragma once

#include "BaseIfModule.h"

#include <QFileInfo>
#include <QFileInfoList>
#include <QUrl>

#include <Types.h>
#include <Uid.h>
#include <MutexQueue.h>
#include <QQString.h>
#include <QQStringList.h>
class BaseErrorCode;

class InputSettings;

class ImageAcquisition : public BaseIfModule
{
    Q_OBJECT
public:
    explicit ImageAcquisition(IfConsoleApp *parent = nullptr);

public slots:
    void initialize();

public: // const
    QFileInfoList fileInfoList() const;

signals:
    void allFiles(const QFileInfoList &fis);
    void empty();
    void startProcessing(const Count nFiles);
    void finishedProcessing(const Count nProcessed);
    void processing(const QFileInfo &fi);
    void processed(const Count nProcessed, const QFileInfo &fi);
    void processError(const Count nNull, const QFileInfo &fi, const BaseErrorCode &ec);

public: // non-const
    void start(const QUrl &url);

public: // pointers

private:
    void startFiles(const QUrl &url, const QUrlQuery &query);
    void startHotDir(const QUrl &url, const QUrlQuery &query);
    void startHttp(const QUrl &url, const QUrlQuery &query);
    bool processFiles(const QFileInfoList fis);
    BaseErrorCode processFile(const QFileInfo fi);

    static QQStringList enumerateExtensions(const QUrlQuery &query);
    static QDir dir(const QUrl &url);

private:
    QFileInfoList mFileInfoList;
    MutexQueue<Uid> mCacheUidQueue;
};

inline QFileInfoList ImageAcquisition::fileInfoList() const { return mFileInfoList; }
