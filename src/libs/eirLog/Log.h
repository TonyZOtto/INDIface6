#pragma once

#include <QObject>

#include <QString>
#include <QUrl>

class Log : public QObject
{
    Q_OBJECT
public: // types
    enum Format
    {
        $nullFormat = 0,
        $baseFormat = 100,
        FormatTxtSingle,
        FormatTxtMulti,
        $endFormat
    };
    Q_ENUM(Format)

    enum Scheme
    {
        $nullOutput = 0,
        $baseOutput = 200,
        OutputTxtFile,
        OutputTroll,
        $endOutput
    };
    Q_ENUM(Scheme)

public: // ctors
    explicit Log(QObject *parent = nullptr);

public slots:

public: // const

public: // non-const

public: // static
    static Format format(const QString &aString);
    static QString formatName(const Format aFormat);
    static Scheme scheme(const QString &aString);
    static Scheme scheme(const QUrl &aUrl);
    static QString schemeName(const Scheme aScheme);


signals:
};
