#include "BaseWorkerTask.h"

#include "../eIRexe/Log.h"

BaseWorkerTask::BaseWorkerTask() {}
BaseWorkerTask::BaseWorkerTask(const Key &taskKey, const KeyMap &input,
                               const KeyMap &config, KeyMap *output)
    : mTaskIdent(Ident(taskKey)), mInput(input), mConfig(config), mpOutput(output) {;}

void BaseWorkerTask::run()
{
//    TWARN("In pure virtual: BaseWorkerTask::run()");
    WPOINTER(KeyMap, mpOutput);
    if (mpOutput)
    {
        mpOutput->insert(mInput, "Input");
        mpOutput->insert(mConfig, "Config");
    }
}

