#pragma once
#include "eIRbase.h"

#include "AText.h"

#include <QChar>
#include <QList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>

class EIRBASE_EXPORT KeySeg : public AText
{
public: // types
    typedef QList<KeySeg> List;

public: // ctors
    explicit KeySeg() {;}
    KeySeg(const char * pch) { set(pch); }
    KeySeg(const AText &atx) { set(atx); }
    KeySeg(const QByteArray &qba) { set(qba); }
    KeySeg(const QString &qs) { set(qs); }

public: // const
    QString toUpper() const;
    QString toString() const;
    QString operator() () const { return toString(); }
    operator QString () const { return toString(); }

public:
    void set(const char * pch);
    void set(const AText &atx);
    void set(const QByteArray &qba);
    void set(const QString &qs);

private: // static
    static char validFirstChar(const char ch);
    static char validNextChar(const char ch);
};
