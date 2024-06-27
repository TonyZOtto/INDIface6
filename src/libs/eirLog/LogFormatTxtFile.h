#pragma once

#include <QObject>
#include "LogFormat.h"

class LogFormatTxtFile : public LogFormat
{
    Q_OBJECT
public:
    explicit LogFormatTxtFile(QObject *parent = nullptr);

signals:
};
