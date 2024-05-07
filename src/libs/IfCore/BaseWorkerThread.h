#pragma once

#include <QThread>

#include <QMap>

#include "../eIRbase/Key.h"
#include "../eIRbase/KeyMap.h"

class BaseWorkerTask;

class BaseWorkerThread : public QThread
{
    Q_OBJECT
public: // ctors
    explicit BaseWorkerThread(QObject *parent = nullptr);

public: // ctors

public: // const

signals:
    void taskComplete(const Key &taskKey);
    void taskError(const Key &taskKey);

public: // non-const
    void add(const Key &taksKey, BaseWorkerTask * task);

public: // virtual non-const
    virtual void run() = 0; // pure

private:
    Key::List mKeyList;
    QMap<Key, BaseWorkerTask*> mKeyTaskMap;
    QMap<Key, KeyMap> mKeyResultsMap;
};
