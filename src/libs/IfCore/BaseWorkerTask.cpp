#include "BaseWorkerTask.h"

#include "../eIRexe/Log.h"

BaseWorkerTask::BaseWorkerTask() {}
BaseWorkerTask::BaseWorkerTask(const Key &taskKey, const KeyMap &input,
                               const KeyMap &config, KeyMap *output)
    : mTaskIdent(Ident(taskKey)), mInput(input), mConfig(config), mpOutput(output) {;}

Key BaseWorkerTask::taskKey() const
{
    return ident().key();
}

QVariant BaseWorkerTask::input(const Key &key, const QVariant &defalt) const
{
    return input().value(key, defalt);
}

KeyMap BaseWorkerTask::output() const
{
    Q_CHECK_PTR(mpOutput);
    return *mpOutput;
}

QVariant BaseWorkerTask::output(const Key &key, const QVariant &defalt) const
{
    return output().value(key, defalt);
}

void BaseWorkerTask::output(const Key &key, const QVariant &var)
{
    Q_CHECK_PTR(mpOutput);
    mpOutput->insert(key, var);
}
