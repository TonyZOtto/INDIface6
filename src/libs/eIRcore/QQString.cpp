#include "QQString.h"

QQString::QQString() {;}
QQString::QQString(const QString &other) : QString(other) {;}

QQStringList QQString::split(const char ch)
{
    return split(ch);
}

QString QQString::toString() const
{
    return (QString)(*this);
}
