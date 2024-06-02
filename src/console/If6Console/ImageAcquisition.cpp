#include "ImageAcquisition.h"

#include <QDir>
#include <QUrlQuery>

#include <BaseErrorCode.h>
#include <BaseImage.h>
#include <ColorImage.h>

#include "IfConsoleApp.h"
#include "InputSettings.h"

ImageAcquisition::ImageAcquisition(IfConsoleApp *parent)
    : BaseIfModule{parent}
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
    if (cFIs.isEmpty())
        emit empty();
    else
        processFiles(cFIs);
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

bool ImageAcquisition::processFiles(const QFileInfoList fis)
{
    emit allFiles(fis);
    emit startProcessing(fis.count());
    Count nProcessed = 0, nNull = 0;
    foreach (const QFileInfo cFI, fis)
    {
        emit processing(cFI);
        const BaseErrorCode cEC = processFile(cFI);
        if (cEC.isError())
            emit processError(++nNull, cFI, cEC);
        else
            emit processed(++nProcessed, cFI);
    }
    emit finishedProcessing(nProcessed);
    return 0 == nNull;
}

BaseErrorCode ImageAcquisition::processFile(const QFileInfo fi)
{
    BaseErrorCode result;
    const QImage cFileImage(fi.filePath());
    if (cFileImage.isNull())
        result = BaseErrorCode("ImageAcquisition/processFile/NullFileImage",
                               "File QImage " + fi.filePath() + " is null");
    if (result.notError())
    {
        const ColorImage cColorImage(cFileImage);
        if (cColorImage.isNull())
            result = BaseErrorCode("ImageAcquisition/processFile/NullColorImage",
                                   "ColorImage for" + fi.filePath() + " is null");
        if (result.notError())
            const Uid cUid = app()->addCache(fi.baseName(), cColorImage);
    }

    return result;
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
