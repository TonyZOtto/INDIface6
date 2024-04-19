#pragma once

#include <QObject>

#include <BaseExecutable.h>
#include <ConsoleApplication.h>
#include <ImageCache.h>

class IfConsoleApp : public ConsoleApplication
{
    Q_OBJECT
public:
    IfConsoleApp(int argc, char *argv[]);

public: // non-const

public slots:
    virtual void initialize();
    void start();

signals:
    void initialized();

private:
    ImageCache mImageCache;

};
