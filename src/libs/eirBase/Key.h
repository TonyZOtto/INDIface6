#pragma once
#include "eIRbase.h"

#include <QChar>
#include <QList>
#include <QString>

#include "AText.h"
#include "KeySeg.h"
#include "Types.h"

class EIRBASE_EXPORT Key
{
public: // types
    typedef QList<Key> List;

public: // ctors
    Key() {;}
    Key(const char * psz) { set(psz); }
    Key(const AText &atx) { set(atx); }
    Key(const QString &qs) { set(qs); }
    Key(const KeySeg::List &segs) { set(segs); }
    Key(const char * chars,
                const char * chars1,
                const char * chars2=0,
        const char * chars3=0) { set(chars, chars1, chars2, chars3); }

public: // const
    bool isNull() const;
    bool isEmpty() const;
    bool isSectioned() const;
    bool notNull() const { return ! isNull(); }
    bool isValid(const Index ix) const;
    bool contains(const char ch) const;
    Count count() const;
    KeySeg segment(const Index ix) const;
    KeySeg::List segments() const;
    KeySeg::List segments(const Index ix, const Index n=-1) const;
    QString sortable() const;
    QString toString() const;
    operator QString () const { return toString(); }
    QString operator () () const { return toString(); }
    bool operator < (const Key &rhs) const;
    bool operator == (const Key &rhs) const;

public: // non-const
    void set(const char * pch);
    void set(const AText &atx);
    void set(const QString &qs);
    void set(const KeySeg::List &segs);
    void set(const char * chars,
                const char * chars1,
                const char * chars2=0,
                const char * chars3=0);
    void append(const QString &s);
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

