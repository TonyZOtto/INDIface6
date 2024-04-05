#pragma once
#include "eIRexe.h"

#include <QObject>

#include <QQueue>
#include <QUrl>
class QVariant;

#include "../eIRbase/Boolean.h"
#include "../eIRbase/Types.h"
#include "LogItem.h"
#include "LogObject.h"
#include "OutputLogUrl.h"
class BaseLogOutput;

class EIREXE_EXPORT Logger : public QObject
{
    Q_OBJECT
public: // types

public: // ctors
    explicit Logger(QObject *parent = nullptr);

public: // const

public slots:

public: // non-const
    bool open(const OutputLogUrl &url,
              const Log::Level maxLevel=Log::$nullLevel,
              const Log::Level minLevel=Log::$nullLevel);
    bool open(const OutputLogUrl &url, const Log::LevelFlags flags);
    bool start();
    bool hookTrollIn();
    bool hookTrollOut();
    void add(LogItem *li);

private:
    bool openFile(const OutputLogUrl &url, const Log::LevelFlags flags);
    bool openTroll(const OutputLogUrl &url, const Log::LevelFlags flags);
    bool openSql(const OutputLogUrl &url, const Log::LevelFlags flags);


private: // static
    static Boolean compare(const Log::Compare c, const QVariant &expected, const QVariant &actual);
    static Boolean compare(const Log::Compare c, const QPartialOrdering qpo);
    static bool equal(const QPartialOrdering qpo);
    static bool greater(const QPartialOrdering qpo);

signals:
    void queued(const LogItem &li);
    void queueCount(const Count k);
    void queueEmpty();

private:
    QQueue<LogItem *> mInputItemQueue;
    QList<BaseLogOutput *> mOutputList;
};
