#pragma once
#include "IfCore.h"

#include <QRunnable>

#include "../eIRbase/Key.h"

class IFCORE_EXPORT BaseWorkerTask : public QRunnable
{
public:
    BaseWorkerTask();

public: // virtual non-const
    virtual Key taskKey() const = 0; // make it pure

};
