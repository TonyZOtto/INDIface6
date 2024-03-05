#pragma once
#include "eIRexe.h"

#include <QObject>

#include <QUrl>
class QVariant;

#include "../eIRbase/Boolean.h"
#include "LogObject.h"

class EIREXE_EXPORT Logger : public QObject
{
    Q_OBJECT
public: // types

public: // ctors
    explicit Logger(QObject *parent = nullptr);

public: // const

public slots:

public: // non-const
    bool open(const QUrl &url=QUrl(),
              const Log::Level maxLevel=Log::$nullLevel,
              const Log::Level minLevel=Log::$nullLevel);
    bool open(const QUrl &url, const Log::LevelFlags flags);
    bool hookTrollIn();
    bool hookTrollOut();

private: // static
    static Boolean compare(const Log::Compare c, const QVariant &expected, const QVariant &actual);
    static Boolean compare(const Log::Compare c, const QPartialOrdering qpo);
    static bool equal(const QPartialOrdering qpo);
    static bool greater(const QPartialOrdering qpo);

signals:
};
