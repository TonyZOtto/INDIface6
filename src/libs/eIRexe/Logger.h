#pragma once
#include"eIRexe.h"

#include <QObject>

class EIREXE_EXPORT Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);

signals:
};
