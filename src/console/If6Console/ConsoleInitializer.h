#pragma once

#include <QObject>

class IfConsoleApp;

class ConsoleInitializer : public QObject
{
    Q_OBJECT
public: // ctors
    explicit ConsoleInitializer(IfConsoleApp *parent = nullptr);

public: // const


public: // pointers
    IfConsoleApp * app();

public: // non-const

public slots:
    void initBase();

signals:

private:
    IfConsoleApp * mpConsoleApp=nullptr;
};

inline IfConsoleApp *ConsoleInitializer::app()
{
    return mpConsoleApp;
}
