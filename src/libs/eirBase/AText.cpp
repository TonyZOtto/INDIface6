#include "AText.h"

#include "Types.h"

AText::AText(const char *psz)
    : QByteArray(psz)
{
    qDebug() << Q_FUNC_INFO << psz << constData();
}

QString AText::toString() const
{
    return QString(*this);
}

char AText::takeFirstChar()
{
    char result = 0;
    if ( ! isEmpty()) result = *(first(1)).data();
    removeFirst();
    return result;
}

void AText::set(const QString &s)
{
    *this = AText(s);
}

void AText::set(const QString &fmt, const QVariantList &vars)
{
    AText result(fmt);
    for (Index ix = 0; ix < vars.count(); ++ix)
        result.replace(("%"+QString::number(ix)).toLocal8Bit(),
                       vars[ix].toString().toLocal8Bit());
    set(result);
}

// static
QStringList AText::toStringList(const List atl)
{
    QStringList result;
    foreach (AText at, atl)
        result << at.toString();
    return result;
}
