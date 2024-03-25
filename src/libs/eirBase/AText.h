//!file {Eclipse6}/root/src/libs/eirBase6/AText.h ASCII Text
#pragma once
#include "eirBase.h"

#include <QByteArray>
#include <QByteArrayList>
#include <QString>
#include <QVariantList>

class EIRBASE_EXPORT AText : public QByteArray
{
public: // types
    typedef QByteArrayList List;

public: // ctors
    AText() {;}
    AText(const QByteArray &ba) : QByteArray(ba) {;}
    AText(const QString &s) : QByteArray(s.toLocal8Bit()) {;}
    AText(const char * pch) : QByteArray(pch) {;}
    AText(const char ch) : QByteArray(1, ch) {;}

public: // const
    QString toString() const;

public: // non-const
    char takeFirstChar();
    void set(const QString &s);
    void set(const QString &fmt, const QVariantList &vars);

public: // static
    static QStringList toStringList(const AText::List atl);
};
