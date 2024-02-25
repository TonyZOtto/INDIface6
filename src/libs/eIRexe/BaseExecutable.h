#pragma once
#include"eIRexe.h"

#include <QObject>

class QCoreApplication;

class EIREXE_EXPORT BaseExecutable : public QObject
{
    Q_OBJECT

protected: // ctors
    explicit BaseExecutable(QObject * parent=nullptr);

public: // const
    bool isNull() const;
    bool isCore() const;

public: // non-const
    void newCore(int argc, char **argv);

public: // pointers
    QCoreApplication *core();

signals:

private:
    QCoreApplication * mpCoreApp=nullptr;
};

inline QCoreApplication *BaseExecutable::core()
{
    Q_CHECK_PTR(mpCoreApp); return mpCoreApp;
}


