#include "Logger.h"

Logger::Logger(QObject *parent)
    : QObject{parent}
{
    setObjectName("Logger");
}

bool Logger::open(const QUrl &url, const Log::Level maxLevel, const Log::Level minLevel)
{

}
