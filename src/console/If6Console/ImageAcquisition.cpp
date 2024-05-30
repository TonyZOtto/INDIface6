#include "ImageAcquisition.h"

#include <QDir>
#include <QUrlQuery>

#include <BaseImage.h>

#include "InputSettings.h"

ImageAcquisition::ImageAcquisition(QObject *parent)
    : QObject{parent}
{
    setObjectName("ImageAcquisition");
}

void ImageAcquisition::initialize()
{
//    settings()->read();
}

void ImageAcquisition::start(const QUrl &url)
{
    setObjectName("ImageAcquisition:" + url.toString());
    const QString cScheme = url.scheme();
    QUrlQuery cQuery = QUrlQuery(url.query());
    if ("files" == cScheme)
        startFiles(url, cQuery);
    else if ("dir" == cScheme)
        startHotDir(url, cQuery);
    else if ("http" == cScheme)
        startHttp(url, cQuery);
}

void ImageAcquisition::startFiles(const QUrl &url, const QUrlQuery &query)
{
    QQStringList cExtList = enumerateExtensions(query);
    // TODO handle file name wildcard query item
    const QDir cDir = dir(url);
    const QQStringList cNameFilters = BaseImage::nameFilters(cExtList);
    const QFileInfoList cFIs = cDir.entryInfoList(cNameFilters);
    qDebug() << Q_FUNC_INFO << cFIs;
}

void ImageAcquisition::startHotDir(const QUrl &url, const QUrlQuery &query)
{
    Q_ASSERT(!"MUSTDO"); // MUSTDO startHotDir()
    Q_UNUSED(url); Q_UNUSED(query);
}

void ImageAcquisition::startHttp(const QUrl &url, const QUrlQuery &query)
{
    Q_ASSERT(!"MUSTDO"); // MUSTDO startHttp()
    Q_UNUSED(url); Q_UNUSED(query);
}

QQStringList ImageAcquisition::enumerateExtensions(const QUrlQuery &query)
{
    QQStringList result;
    if (query.hasQueryItem("FileExt"))
    {
        QQString cString = query.queryItemValue("FileExt");
        const QQStringList cSpecList = cString.split(';');
        QQStringList tExtList = BaseImage::supportedFileExtensionList();
        result = tExtList.intersect(cSpecList);
    }
    return result;
}

QDir ImageAcquisition::dir(const QUrl &url)
{
    QDir result;
    const QString cPath = url.path();
    const QFileInfo cFI = QFileInfo(cPath);
    if (cFI.exists() && cFI.isReadable())
        result = cFI.dir();
    return result;
}
