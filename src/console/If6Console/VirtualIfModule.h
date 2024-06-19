#pragma once

#include <QObject>

class IfConsoleApp;

class VirtualIfModule : public QObject
{
    Q_OBJECT
public: // ctors
    explicit VirtualIfModule(IfConsoleApp *parent = nullptr);

public slots:
    virtual void initialize() = 0;
    virtual void run() = 0;

signals:

public: // const

public: // non const

public: // pointers
    IfConsoleApp * app();

private:
    IfConsoleApp * mpApp;
};

inline IfConsoleApp *VirtualIfModule::app() { Q_CHECK_PTR(mpApp); return mpApp; }
