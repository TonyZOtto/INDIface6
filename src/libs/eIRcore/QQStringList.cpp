#include "QQStringList.h"

#include "QQString.h"

QQStringList::QQStringList() {;}
QQStringList::QQStringList(const QList<QQString> &other) : QList<QQString>(other) {;}

QQStringList QQStringList::intersect(const QQStringList &rhs)
{
    return intersect(*this, rhs);
}

QStringList QQStringList::toStringList() const
{
    QStringList result;
    foreach (QQString qqs, *this)
        result.append(qqs.toString());
    return result;
}

void QQStringList::append(const QQString &s)
{
    QList<QQString>::append(s);
}


// static
QQStringList QQStringList::intersect(const QQStringList &lhs, const QQStringList &rhs)
{
    QQStringList result;
    foreach(QQString s, lhs)
        if (rhs.contains(s))
            result.append(s);
    return result;
}

EIRCORE_EXPORT QQStringList operator & (const QQStringList &lhs, const QQStringList &rhs)
{
    return QQStringList::intersect(lhs, rhs);
}

