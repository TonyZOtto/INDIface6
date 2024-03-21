#pragma once

#include <QObject>
#include "BaseLogOutput.h"

class FileLogOutput : public BaseLogOutput
{
    Q_OBJECT
public:
    explicit FileLogOutput(QObject *parent = nullptr);
};
