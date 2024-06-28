#include "ImageWriterOutput.h"

#include <QCoreApplication>

QString ImageWriterOutput::smBaseDirName;

ImageWriterOutput::ImageWriterOutput(const Image::Type aIType, QObject *parent)
    : QObject{parent}
    , cmIType(aIType)
{
    setObjectName("ImageWriterOutput:" + Image::typeName(aIType));
}

bool ImageWriterOutput::set(const QString aOutputDir)
{
    bool result = false;
    mOutputDir = QDir::current();
    QDir tDir = mOutputDir;
    QString tAppDirPath = QCoreApplication::applicationDirPath();
    tDir.cd(tAppDirPath);
    if ( ! smBaseDirName.isEmpty())
    {
        tDir.mkpath(smBaseDirName); // TODO WEXPECT
        tDir.cd(smBaseDirName);
    }
    tDir.mkpath(aOutputDir);
    result = tDir.cd(aOutputDir);
    if (result) mOutputDir = tDir;
    return result;
}
