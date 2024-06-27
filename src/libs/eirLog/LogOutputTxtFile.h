#pragma once

#include <QObject>
#include "LogOutput.h"

class LogOutputTxtFile : public LogOutput
{
    Q_OBJECT
public:
    explicit LogOutputTxtFile(QObject *parent = nullptr);

signals:
};
