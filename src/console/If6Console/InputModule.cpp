#include "InputModule.h"

#include <QDir>
#include <QUrlQuery>

#include <BaseErrorCode.h>
#include <BaseImage.h>
#include <ColorImage.h>
#include <FrameData.h>
#include <Ident.h>
#include <IfCache.h>
#include <MillisecondTime.h>

#include "IfConsoleApp.h"
#include "InputSettings.h"

InputModule::InputModule(IfConsoleApp *parent)
    : VirtualIfModule{parent}
{
    setObjectName("InputModule");
}

void InputModule::initialize()
{
    emit initialized(this);
}

void InputModule::run()
{
    emit running();
    const QUrl cUrl = app()->get("Input/Url").toUrl();
    start(cUrl);
}

void InputModule::start(const QUrl &url)
{
    setObjectName("InputModule:" + url.toString());
    const QString cScheme = url.scheme();
    const QUrlQuery cQuery = QUrlQuery(url.query());
    qInfo() << "Input/URL:" << url << cScheme << cQuery.toString();
    if ("files" == cScheme)
        startFiles(url, cQuery);
    else if ("dir" == cScheme)
        startHotDir(url, cQuery);
    else if ("http" == cScheme)
        startHttp(url, cQuery);
}

void InputModule::startFiles(const QUrl &url, const QUrlQuery &query)
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

void InputModule::startHotDir(const QUrl &url, const QUrlQuery &query)
{
    Q_ASSERT(!"MUSTDO"); // MUSTDO startHotDir()
    Q_UNUSED(url); Q_UNUSED(query);
}

void InputModule::startHttp(const QUrl &url, const QUrlQuery &query)
{
    Q_ASSERT(!"MUSTDO"); // MUSTDO startHttp()
    Q_UNUSED(url); Q_UNUSED(query);
}

bool InputModule::processFiles(const QFileInfoList fis)
{
    emit allFiles(fis);
    emit startProcessing(fis.count());
    qInfo() << "===Prtocessing Files: ";
    Count nProcessed = 0, nNull = 0;
    foreach (const QFileInfo cFI, fis)
    {
        emit processing(cFI);
        const BaseErrorCode cEC = processFile(cFI);
        if (cEC.isError())
            emit processError(++nNull, cFI, cEC);
        else
            emit processed(++nProcessed, cFI);
        qInfo() << nProcessed << cFI.baseName();
    }
    emit finishedProcessing(nProcessed);
    return 0 == nNull;
}

BaseErrorCode InputModule::processFile(const QFileInfo fi)
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
        {
            Ident tFrameIdent(fi.baseName());
            FrameData tFrameData(tFrameIdent);
            QVariant tColorImageVar = cColorImage.toVariant();
            tFrameData.insert("Input/Source/URL", app()->inputMap().value("URL"));
            tFrameData.insert("Input/Source/EMS", MillisecondTime::current().toString("DyyyyMMdd-Thhmmsszzz"));
            tFrameData.insert("Input/Source/FileName", fi.baseName());
            tFrameData.insert("Input/Source/FileImage", cFileImage);
            tFrameData.insert("Input/Source/ColorImage", tColorImageVar);
            const Uid cUid = app()->cache()->frame(tFrameData);
            mCacheUidQueue.enqueue(cUid);
        }
    }
    return result;
}

QQStringList InputModule::enumerateExtensions(const QUrlQuery &query)
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

QDir InputModule::dir(const QUrl &url)
{
    QDir result;
    const QString cPath = url.path();
    const QFileInfo cFI = QFileInfo(cPath);
    if (cFI.exists() && cFI.isReadable())
        result = cFI.dir();
    return result;
}
