#pragma once
#include "eIRexe.h"

#include <QObject>

#include <QUrl>

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
              const Log::Level maxLevel=Log::$null,
              const Log::Level minLevel=Log::$null);
    bool open(const QUrl &url, const Log::LevelFlags flags);
    bool hookTrollIn();
    bool hookTrollOut();


signals:
};
