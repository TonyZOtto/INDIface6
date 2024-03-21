#pragma once

#include <QObject>
#include "BaseLogOutput.h"

class TrollLogOutput : public BaseLogOutput
{
    Q_OBJECT
public:
    explicit TrollLogOutput(QObject *parent = nullptr);
};
