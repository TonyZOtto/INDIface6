#pragma once

#include <QObject>
#include "LogOutput.h"

class LogOutputTroll : public LogOutput
{
    Q_OBJECT
public:
    explicit LogOutputTroll(QObject *parent = nullptr);

signals:
};
