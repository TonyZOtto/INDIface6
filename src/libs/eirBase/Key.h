#pragma once
#include "eIRbase.h"

#include <QChar>
#include <QString>

#include "AText.h"
#include "KeySeg.h"

class EIRBASE_EXPORT Key
{
public: // ctors
    Key() {;}
    Key(const char * pch) { set(pch); }
    Key(const AText &atx) { set(atx); }
    Key(const QString &qs) { set(qs); }

public: // const
    bool isNull() const;
    bool notNull() const { return ! isNull(); }
    QString toString() const;
    bool operator < (const Key &rhs) const;

public: // non-const
    void set(const char * pch);
    void set(const AText &atx);
    void set(const QString &qs);

private: // static
//    static KeySeg::List split(const char * pch, const QChar hinge=QChar('/'));
    static KeySeg::List split(const AText &atx, const QChar hinge=QChar('/'));
//    static KeySeg::List split(const QString &qs, const QChar hinge=QChar('/'));
    static AText joinAText(const KeySeg::List &segs, const QChar hinge=QChar('/'));
    static QString joinString(const KeySeg::List &segs, const QChar hinge=QChar('/'));

private:
    KeySeg::List mSegments;
};

