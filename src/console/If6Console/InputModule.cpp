#include "InputModule.h"

#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QUrlQuery>

#include <BaseErrorCode.h>
#include <BaseImage.h>
#include <ColorImage.h>
#include <FrameData.h>
#include <Ident.h>
#include <IfCache.h>
#include <Log.h>
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
    QFileInfoList tFIList;
    const QDir cDir = dir(url);
    if ( ! cDir.isEmpty())
    {
        const QQStringList cNameFilters = BaseImage::nameFilters(cExtList);
        const QFileInfoList cQFIL = cDir.entryInfoList(cNameFilters, QDir::Files);
        tFIList = cQFIL;
    }
    qDebug() << Q_FUNC_INFO << url << query.toString() << cDir << tFIList;
    if (tFIList.isEmpty())
        emit empty();
    else
        processFiles(tFIList);
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

bool InputModule::processFiles(const QFileInfoList &aFIList)
{
    emit allFiles(aFIList);
    emit startProcessing(aFIList.count());
    PROGRESS("===Processing " + QString::number(aFIList.count()) + " Files");
    Count nProcessed = 0, nNull = 0;
    DETAIL(QQFileInfo::toListDebugStrings(aFIList).join('\n'));
    foreach (const QFileInfo cFI, aFIList)
    {
        emit processing(cFI);
        INFO("---Processing: " + cFI.baseName());
        const BaseErrorCode cEC = processFile(cFI);
        if (cEC.isError())
        {
            TWARN("###" + cEC.toString());
            emit processError(++nNull, cFI, cEC);
        }
        else
        {
            emit processed(++nProcessed, cFI);
        }
//        qInfo() << nProcessed << cFI.fileName();
    }
    emit finishedProcessing(nProcessed);
    return 0 == nNull;
}

BaseErrorCode InputModule::processFile(const QFileInfo fi)
{
    BaseErrorCode result;
    QImage tFileImage;
    QFile tFile(fi.filePath());
    tFile.open(QIODevice::ReadOnly);
    if ( ! tFile.isOpen())
        result = BaseErrorCode(&tFile);

    QByteArray tBytes = tFile.readAll();
    if (tBytes.isEmpty())
        result = BaseErrorCode("InputModule/processFile/NullFileData",
                           "File " + fi.filePath() + " is empty");
    else
        tFileImage = QImage::fromData(tBytes);

    if (result.notError())
    {
        if (tFileImage.isNull())
            result = BaseErrorCode("InputModule/processFile/NullFileImage",
                                   "File QImage " + fi.filePath() + " is null");
    }

    if (result.notError())
    {
        const ColorImage cColorImage(tFileImage);
        if (cColorImage.isNull())
            result = BaseErrorCode("InputModule/processFile/NullColorImage",
                                   "ColorImage for" + fi.filePath() + " is null");
        if (result.notError())
        {
            Ident tFrameIdent(fi.baseName());
            FrameData tFrameData(tFrameIdent);
            QVariant tColorImageVar = cColorImage.toVariant();
            tFrameData.insert("Input/Source/URL", app()->inputMap().value("URL"));
            tFrameData.insert("Input/Source/EMS", MillisecondTime::current().toString("DyyyyMMdd-Thhmmsszzz"));
            tFrameData.insert("Input/Source/FileName", fi.baseName());
            tFrameData.insert("Input/Source/FileBytes", tBytes);
            tFrameData.insert("Input/Source/FileImage", tFileImage);
            tFrameData.insert("Input/Source/ColorImage", tColorImageVar);
            const Uid cUid = app()->cache()->frame(tFrameData);
            mCacheUidQueue.enqueue(cUid);
        }
    }
    qDebug() << result.toString();
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
    const QString cPath(url.path());
    const QDir cDir(cPath);
    if (cDir.isReadable()) result = cDir;
    return result;
}
