#pragma once

#include <QObject>

#include <QFileInfoList>
#include <QUrl>

#include <QQString.h>
#include <QQStringList.h>

class ImageAcquisition : public QObject
{
    Q_OBJECT
public:
    explicit ImageAcquisition(QObject *parent = nullptr);

public: // const
    QFileInfoList fileInfoList() const;

signals:

public: // non-const
    void start(const QUrl &url);

private:
    void startFiles(const QUrl &url, const QUrlQuery &query);
    void startHotDir(const QUrl &url, const QUrlQuery &query);
    void startHttp(const QUrl &url, const QUrlQuery &query);

    static QQStringList enumerateExtensions(const QUrlQuery &query);
    static QDir dir(const QUrl &url);

private:
    QFileInfoList mFileInfoList;
};

inline QFileInfoList ImageAcquisition::fileInfoList() const
{
    return mFileInfoList;
}
