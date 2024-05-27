#pragma once
#include "eIRbase.h"

#include <QChar>
#include <QList>
#include <QString>

#include "AText.h"
#include "KeySeg.h"

class EIRBASE_EXPORT Key
{
public: // types
    typedef QList<Key> List;

public: // ctors
    Key() {;}
    Key(const char * pch) { set(pch); }
    Key(const AText &atx) { set(atx); }
    Key(const QString &qs) { set(qs); }

public: // const
    bool isNull() const;
    bool notNull() const { return ! isNull(); }
    KeySeg::List segments() const;
    QString toString() const;
    QString operator () () const { return toString(); }
    bool operator < (const Key &rhs) const;

public: // non-const
    void set(const char * pch);
    void set(const AText &atx);
    void set(const QString &qs);
    void prepend(const KeySeg &seg);
    void prepend(const Key &key);

private: // static
    static KeySeg::List split(const AText &atx, const QChar hinge=QChar('/'));
    static AText joinAText(const KeySeg::List &segs, const QChar hinge=QChar('/'));
    static QString joinString(const KeySeg::List &segs, const QChar hinge=QChar('/'));

private:
    KeySeg::List mSegments;
};

inline KeySeg::List Key::segments() const
{
    return mSegments;
}

