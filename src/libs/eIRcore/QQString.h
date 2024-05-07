#pragma once

#include <QString>

#include "QQStringList.h"

class EIRCORE_EXPORT QQString : public QString
{
public:
    QQString();
    QQString(const QString &other);

public: // const
    QQStringList split(const char ch);
    QString toString() const;
};
