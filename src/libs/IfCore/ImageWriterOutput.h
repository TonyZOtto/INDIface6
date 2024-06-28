#pragma once

#include <QObject>

#include <QDir>
#include <QString>

#include "Image.h"

class ImageWriterOutput : public QObject
{
    Q_OBJECT
public: // ctors
    explicit ImageWriterOutput(const Image::Type aIType,
                               QObject *parent = nullptr);

signals:

public: // const
    Image::Type type() const;
    QDir outputDir() const;


public: // non-const
    bool set(const QString aOutputDir);

public: // static
    static void setBase(const QString aBaseDirName);


private:
    const Image::Type cmIType=Image::$null;
    QString mDirName;
    QDir mOutputDir;

private:
    static QString smBaseDirName;
};

inline Image::Type ImageWriterOutput::type() const { return cmIType; }
inline QDir ImageWriterOutput::outputDir() const { return mOutputDir; }
inline void ImageWriterOutput::setBase(const QString aBaseDirName) { smBaseDirName = aBaseDirName; }
