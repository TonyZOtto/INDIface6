#pragma once

#include <QObject>
#include "VirtualIfModule.h"

class OutputModule : public VirtualIfModule
{
    Q_OBJECT
public:
    explicit OutputModule(IfConsoleApp *parent = nullptr);

public slots:
    virtual void initialize();
    virtual void run();

signals:
    void initialized(VirtualIfModule * pThis);
    void running();
};
