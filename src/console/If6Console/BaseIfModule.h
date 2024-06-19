#pragma once

#include <QObject>

class IfConsoleApp;

class BaseIfModule : public QObject
{
    Q_OBJECT
public: // ctors
    explicit BaseIfModule(IfConsoleApp *parent = nullptr);

public: // const

public: // non const

public: // pointers
    IfConsoleApp * app();
signals:

private:
    IfConsoleApp * mpApp;
};

inline IfConsoleApp *BaseIfModule::app() { Q_CHECK_PTR(mpApp); return mpApp; }
