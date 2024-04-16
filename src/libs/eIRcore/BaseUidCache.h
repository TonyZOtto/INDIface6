#pragma once

#include <QObject>

#include "../eIRbase/Types.h"

class BaseUidCache : public QObject
{
    Q_OBJECT
public:
    explicit BaseUidCache(QObject *parent = nullptr);

signals:

    // ------------------------ Properties --------------------------
private:
    Count m_maxEntries;
    Count m_maxBytes;
};
