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
