#pragma once
#include "IfCore.h"

#include <QRunnable>

#include <QList>
#include <QVariant>

#include "../eIRbase/Ident.h"
#include "../eIRbase/Key.h"
#include "../eIRbase/KeyMap.h"

class IFCORE_EXPORT BaseWorkerTask : public QRunnable
{
public: // types
    typedef QList<BaseWorkerTask> List;

public: // ctors
    BaseWorkerTask();
protected:
    BaseWorkerTask(const Key &taskKey, const KeyMap &input,
                   const KeyMap &config=KeyMap(), KeyMap *output=nullptr);

public: // const
    Key taskKey() const;
    Ident ident() const;
    KeyMap input() const;
    QVariant input(const Key &key, const QVariant &defalt=QVariant()) const;
    KeyMap config() const;
    QVariant config(const Key &key, const QVariant &defalt=QVariant()) const;
    KeyMap output() const;
    QVariant output(const Key &key, const QVariant &defalt=QVariant()) const;

public: // non-const
    Ident & ident();
    void input(const KeyMap &in);
    void config(const KeyMap &cfg);
    void output(const Key &key, const QVariant &var);

public: // virtual const

public: // virtual non-const
    virtual void run() override = 0; // make it pure

private:
    Ident mTaskIdent;
    KeyMap mInput;
    KeyMap mConfig;
    KeyMap * mpOutput=nullptr;
};

inline Ident BaseWorkerTask::ident() const
{
    return mTaskIdent;
}

inline KeyMap BaseWorkerTask::input() const
{
    return mInput;
}

inline Ident &BaseWorkerTask::ident()
{
    return mTaskIdent;
}

inline void BaseWorkerTask::input(const KeyMap &in)
{
    mInput = in;
}

inline void BaseWorkerTask::config(const KeyMap &cfg)
{
    mConfig = cfg;
}


