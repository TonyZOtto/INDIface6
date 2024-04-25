#pragma once
#include "IfCore.h"

#include <QRunnable>

#include "../eIRbase/Ident.h"
#include "../eIRbase/Key.h"
#include "../eIRbase/KeyMap.h"

class IFCORE_EXPORT BaseWorkerTask : public QRunnable
{
public:
    BaseWorkerTask();
    BaseWorkerTask(const Key &taskKey, const KeyMap &input,
                   const KeyMap &config=KeyMap(), KeyMap *output=nullptr);

public: // const
    Ident ident() const;

public: // non-const
    Ident & ident();
    void input(const KeyMap &in);
    void config(const KeyMap &cfg);

public: // virtual const
    virtual Key taskKey() const = 0; // make it pure

public: // virtual non-const
    virtual void run() override;

private:
    Ident mTaskIdent;
    KeyMap mInput;
    KeyMap mConfig;
    KeyMap *mpOutput=nullptr;
};

inline Ident BaseWorkerTask::ident() const
{
    return mTaskIdent;
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
