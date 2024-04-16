#include "KeySeg.h"

void KeySeg::set(const AText &atx)
{
    AText tInText = atx;
    AText tOutText(validFirstChar(tInText.takeFirstChar()));
    while ( ! tInText.isEmpty())
        tOutText.append(validFirstChar(tInText.takeFirstChar()));
}

void KeySeg::set(const char *pch)
{
    set(AText(pch));
}

void KeySeg::set(const QString &qs)
{
    set(AText(qs));
}

QString KeySeg::toString() const
{
    return QString(QByteArray::constData());
}

// =================== static ====================

char KeySeg::validFirstChar(const char ch)
{
    char result('_');
    static const QRegularExpression scFirstCharsRE("[_ABCDEFGHIJKLMNOPQRSTUVWXYZ]",
                                                   QRegularExpression::CaseInsensitiveOption);
    const QRegularExpressionMatch cFirstREMatch = scFirstCharsRE.match(QString(ch));
    if (cFirstREMatch.isValid()) result = ch;
    return result;
}

char KeySeg::validNextChar(const char ch)
{
    char result('_');
    static const QRegularExpression scNextCharsRE("[_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ]",
                                                  QRegularExpression::CaseInsensitiveOption);
    const QRegularExpressionMatch cNextREMatch = scNextCharsRE.match(QString(ch));
    if (cNextREMatch.isValid()) result = ch;
    return result;
}


