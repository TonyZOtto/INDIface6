#pragma once
#include "eIRcore.h"

#include <QFileInfo>

#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QList>
#include <QIODevice>
#include <QMetaType>
#include <QString>
#include <QStringList>
#include <QTimeZone>

#include "../eIRbase/Types.h"

class EIRCORE_EXPORT QQFileInfo : public QFileInfo
{
public: // types
    QList<QQFileInfo> List;

public: // ctors
    QQFileInfo(const QString &fpath);
    QQFileInfo(const QFileInfo &other);

public: // const
    bool isNull() const;
    bool isSuffix(const QString &sfx) const;
    Count byteCount() const;
    QStringList infoStrings(int verbosity=-1) const;
    QFile * file(const QIODevice::OpenMode &mode,
                 QObject * parent=nullptr) const;
    QString permissionsString() const;

    QDateTime born() const;
    QDateTime modified() const;
    QDateTime used() const;
    QDateTime time(const QFile::FileTime ft,
                   const QTimeZone &tz=QTimeZone::LocalTime) const;

public: // non-const
    void set(const QQFileInfo &fi);
    QFileInfo & it();

public: // static
    static QStringList toListDebugStrings(const QFileInfoList &aList);

private: // const
    QString flagChars() const;
    QString flagString(const bool isSet=true) const;

public: // QMetaType
    QQFileInfo() = default;
    ~QQFileInfo() = default;
    QQFileInfo(const QQFileInfo &) = default;
    QQFileInfo &operator=(const QQFileInfo &) = default;


public: // debug
    QString toDebugString() const;

private:
};

Q_DECLARE_METATYPE(QQFileInfo);
