#pragma once
#include "eIRcore.h"

#include <QList>

class QQString;

class EIRCORE_EXPORT QQStringList : public QList<QQString>
{
public:
    QQStringList();
    QQStringList(const QList<QQString> &other);

public: // const
    QQStringList intersect(const QQStringList &rhs);
    QStringList toStringList() const;
    operator QStringList () const { return toStringList(); }

public: // non-const
    void append(const QQString &s);

public: // static
    static QQStringList intersect(const QQStringList &lhs, const QQStringList &rhs);

    friend QQStringList operator & (const QQStringList &lhs, const QQStringList &rhs);
};
