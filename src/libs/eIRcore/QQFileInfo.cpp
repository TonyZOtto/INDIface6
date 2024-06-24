#include "QQFileInfo.h"

QQFileInfo::QQFileInfo(const QString &fpath) : QFileInfo(fpath) {;}
QQFileInfo::QQFileInfo(const QFileInfo &other) : QFileInfo(other) {;}

bool QQFileInfo::isNull() const
{
    return fileName().isEmpty();
}

bool QQFileInfo::isSuffix(const QString &sfx) const
{
    return suffix().compare(sfx, Qt::CaseInsensitive);
}

QStringList QQFileInfo::infoStrings(int verbosity) const
{
    QStringList result;
    const QString cPath = path();
    const QDir cDir(cPath);
    if (verbosity < 0) verbosity = 2;

    if (isFile())
        result << QString("File:               %1").arg(fileName());

    if (dir().isRelative())
        result << QString("Relative Directory: %1").arg(dir().path());
    if ((verbosity > 1 && cDir.isAbsolute())
            || verbosity >= 3)
        result << QString("Absolute Directory: %1").arg(cDir.path());
    if (verbosity > 0)
        result << QString("Flags:              %1").arg(flagString());
    if (verbosity > 1)
        result << QString("NOT Flags:          %1").arg(flagString(false));
    if (verbosity > 0)
        result << QString("Permissions:        %1").arg(permissionsString());
    return result;
}

QString QQFileInfo::permissionsString() const
{
    QString result;
    result += "TODO: permissionsString";
    // TODO QQFileInfo::permissionsString()
    return result;
}

QDateTime QQFileInfo::modified() const
{
    return time(QFileDevice::FileModificationTime,
                QTimeZone::LocalTime);
}

QDateTime QQFileInfo::time(const QFileDevice::FileTime ft,
                           const QTimeZone &tz) const
{
    return fileTime(ft, tz);
}

void QQFileInfo::set(const QQFileInfo &fi)
{
    *this = fi;
}

// static
QStringList QQFileInfo::toListDebugStrings(const QFileInfoList &aList)
{
    QStringList result;
    foreach (const QFileInfo cQFI, aList)
    {
        const QQFileInfo cQQFI(cQFI);
        result.append(cQQFI.toDebugString());
    }
    return result;
}

QString QQFileInfo::flagChars() const
{
    QString result;
    result += isRelative()      ? "L" : "l";
    result += isAbsolute()      ? "A" : "a";
    result += isDir()           ? "D" : "d";
    result += isFile()          ? "F" : "f";
    result += isExecutable()    ? "X" : "x";
    result += isHidden()        ? "H" : "h";
    result += isNativePath()    ? "N" : "n";
    result += isReadable()      ? "R" : "r";
    result += isWritable()      ? "W" : "w";
    result += exists()          ? "E" : "e";
    result += isRoot()          ? "T" : "t";
    result += isSymLink()       ? "S" : "s";
    result += isSymbolicLink()  ? "$" : "s";
    return result;
}

QString QQFileInfo::flagString(const bool isSet) const
{
    QString result;
    QStringList tNames;
    if (isSet == isRelative()) tNames << "Relative";
    if (isSet == isAbsolute()) tNames << "Absolute";
    if (isSet == isDir()) tNames << "Dir";
    if (isSet == isFile()) tNames << "File";
    if (isSet == isExecutable()) tNames << "Executable";
    if (isSet == isHidden()) tNames << "Hidden";
    if (isSet == isNativePath()) tNames << "NativePath";
    if (isSet == isReadable()) tNames << "Readable";
    if (isSet == isWritable()) tNames << "Writable";
    if (isSet == exists()) tNames << "Exists";
    if (isSet == isRoot()) tNames << "Root";
    if (isSet == isSymLink()) tNames << "SymLink";
    if (isSet == isSymbolicLink()) tNames << "SymbolicLink";
    result = tNames.join(',');
    return result;
}

QString QQFileInfo::toDebugString() const
{
    return isNull() ? "{null}"
                    : QString("%1/%2 %3 %4")
        .arg(path(), 20).arg(fileName(), -20)
        .arg(modified().toString("DYYMMdd-Thhmm"), flagChars());
}
