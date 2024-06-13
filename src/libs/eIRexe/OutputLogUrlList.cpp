#include "OutputLogUrlList.h"

#include <QStringList>

OutputLogUrlList::OutputLogUrlList(const QString &aString)
{
    const QStringList cStringList = aString.split(hinge());
    foreach (const QString cUrlString, cStringList)
    {
        append(OutputLogUrl(QUrl(cUrlString)));
    }
}

// static
QChar OutputLogUrlList::smHinge(';');
