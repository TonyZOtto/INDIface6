#include "BaseWorkerThread.h"

BaseWorkerThread::BaseWorkerThread(QObject *parent)
    : QThread{parent}
{
    setObjectName("BaseWorkerThread");
}
