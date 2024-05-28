#include "KeyGenerator.h"

#include <QDateTime>
#include <QDir>
#include <QFileInfo>

QChar KeyGenerator::trigger('%');
QChar KeyGenerator::pathSub('/');

KeyGenerator::KeyGenerator()
    : VariableSet("IdGenerator")
{
    DEFINE_VARIABLESET_CTORS(IDGENERATOR_VARIABLESET);
}

void KeyGenerator::setFaceFormat(const QString & formatStrings)
{
    setFormat("Face", formatStrings);
}

void KeyGenerator::setFrameFormat(const QString & formatStrings)
{
    setFormat("Frame", formatStrings);
}

QString KeyGenerator::faceFormat(void) const
{
    return getFormat("Face");
}

QString KeyGenerator::frameFormat(void) const
{
    return getFormat("Frame");
}

void KeyGenerator::setFormat(const QString & className,
                            const QString & formatStrings)
{
    QStringList qsl(formatStrings.split(';'));
    QString formatString(qsl.takeFirst());
    sortable_format_map.insert(className.toLower(), formatString);

    while ( ! qsl.isEmpty())
    {
        QString s(qsl.takeFirst());
        int x = s.indexOf('=');
        if (x > 1)
        {
            QString className(s.left(x));
            QString formatString(s.mid(x+1));
            sortable_format_map.insert(className.toLower(), formatString);
        }
    }
}

QString KeyGenerator::getFormat(const QString & className) const
{
    return sortable_format_map.value(className.toLower());
}


Key KeyGenerator::face(const QString & className) const
{
    Key key = generate(className, className);
    if (key.isEmpty())   key = generate("Face", className);
    return key;
}

Key KeyGenerator::frame(const QString & className) const
{
    Key key = generate(className, className);
    if (key.isEmpty())   key = generate("Frame", className);
    return key;
}

Key KeyGenerator::generate(const QString & className,
                              const QString & outputClass) const
{
    //pathSub = '/';
    QString result;
    QString format = sortable_format_map[className.toLower()];
    if (format.isEmpty()) return Key();

    QString::const_iterator it = format.begin();
    while (it != format.end())
    {
        QChar cValue(*it++);
        if (trigger != cValue)
        {
            result.append(cValue);
            continue;
        }

        cValue = *it++;

#if 0
        if ('/' == cValue)
        {
            pathSub = *it++;
            continue;
        }
#endif

        qint64 iValue = numericValue(cValue);
        if (iValue < 0)
        {
            result.append(stringValue(cValue, outputClass));
            continue;
        }

        if ('!' == *it)
        {
            ++it;
            result.append(cValue);
            result.append(QString("%1").arg(iValue / 100 * 100, 3, 10, QChar('0')));
        }
        else if (':' == *it)
        {
            ++it;
            bool forceZero = false;
            if ('0' == *it)
            {
                ++it;
                forceZero = true;
            }
            int w = (*it++).digitValue();
            if (iValue || forceZero)
            {
                result.append(cValue);
                result.append(QString("%1").arg(iValue, w, 10, QChar('0')));
            }
        }
        else if (iValue)
        {
            result.append(cValue);
            result.append(QString::number(iValue));
        }
    }

    return Key(result);
}

qint64 KeyGenerator::numericValue(const QChar c) const
{
    switch (c.cell())
    {
    case 'x':   return getDetectRect().center().x();
    case 'y':   return getDetectRect().center().y();
    case 'c':   return getConsistency();
    case 'e':   return getEyeLine().length();
    case 'w':   return getDetectRect().width();
    case 'm':   return getConfidence();
    case 'r':   return getRank();
    case '#':   return getFrameNumber();
    case 'n':   return getFaceNumber();
    case 'l':   return getModifiedMst();
    case 'z':   return getFrameMst();
    case 'q':   return getQuality();
    case 'Q':   return getBestQuality();
    default:    return -1;
    }
}

QString KeyGenerator::stringValue(const QChar c,
                            const QString & outputClass) const
{
    switch (c.cell())
    {
    case '%':   return "%";
    case 'i':   return getFrameKey();
    case 'd':   return getModifiedMst().toString("yyyyMMdd");
    case 't':   return getModifiedMst().toString("hhmmsszzz");
    case 'o':   return outputClass;
    case 'A':   return QFileInfo(getFileName()).absoluteDir().path().replace('/', pathSub);
    case 'R':   return QFileInfo(getFileName()).dir().path().replace('/', pathSub);
    case 'p':   return getPersonKey();
    case 'n':   return QFileInfo(getFileName()).completeBaseName();
    default:    return QString();
    }
}
